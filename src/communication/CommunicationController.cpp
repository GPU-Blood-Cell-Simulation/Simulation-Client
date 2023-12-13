#include "CommunicationController.hpp"

// TODO: remove
#include <chrono>
#include <thread>

#include <stdexcept>
#include <iostream>
#include <sstream>


CommunicationController::CommunicationController(const std::string& facultyLogin, const std::string& facultyPassword, const std::string& edenLogin, const std::string& edenPassword)
{
    if (ssh_init() != SSH_OK)
        throw std::runtime_error("Error while initializing SSH session");

    int verbosity = SSH_LOG_PROTOCOL;
    const char* host = "ssh.mini.pw.edu.pl";
    const char* user = "niecieckip";
    const char* password = "tohl0Cha";  // Use a more secure method for real-world scenarios

    // Initialize the SSH session
    session = ssh_new();
    if (session == NULL) {
        fprintf(stderr, "Error creating SSH session\n");
        return;
    }

    // Set SSH options
    ssh_options_set(session, SSH_OPTIONS_HOST, host);
    ssh_options_set(session, SSH_OPTIONS_USER, user);
    ssh_options_set(session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);



    // Connect to the SSH server
    if (ssh_connect(session) != SSH_OK) {
        fprintf(stderr, "Error connecting to %s\n", host);
        ssh_free(session);
        return;
    }

    verify_host();

    // Authenticate with password
    if (ssh_userauth_password(session, NULL, password) != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Authentication failed\n");
        ssh_disconnect(session);
        ssh_free(session);
        return;
    }

    // Open a channel for executing a command
    channel = ssh_channel_new(session);
    if (channel == NULL) {
        fprintf(stderr, "Error creating SSH channel\n");
        ssh_disconnect(session);
        ssh_free(session);
        return;
    }

    // Execute a command on the remote server
    if (ssh_channel_request_exec(channel, "ls -l") != SSH_OK) {
        fprintf(stderr, "Error executing command\n");
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
        return;
    }

    // Read and print the output of the command
    char buffer[256];
    int nbytes;
    while ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, nbytes, stdout);
    }

    // Close the channel
    ssh_channel_send_eof(channel);
    ssh_channel_free(channel);

    // Disconnect and free resources
    ssh_disconnect(session);
    ssh_free(session);
    
}


CommunicationController::~CommunicationController()
{
    //ssh_channel_send_eof(channel);
    //ssh_channel_close(channel);

    //ssh_channel_free(channel);

    //ssh_disconnect(session);
    //ssh_free(session);

    ssh_finalize();
}


void CommunicationController::verify_host()
{
    switch (ssh_session_is_known_server(session)) {
    case SSH_KNOWN_HOSTS_OK:
        /* OK */

        break;
    case SSH_KNOWN_HOSTS_CHANGED:
        throw std::runtime_error("Host key for server changed. For security reasons, connection is stopped");

    case SSH_KNOWN_HOSTS_OTHER:
        throw std::runtime_error("The host key for this server was not found but an other type of key exists.");

    case SSH_KNOWN_HOSTS_NOT_FOUND:
        /* FALL THROUGH to SSH_SERVER_NOT_KNOWN behavior */

    case SSH_KNOWN_HOSTS_UNKNOWN:
        if (ssh_session_update_known_hosts(session) < 0)
            throw std::runtime_error("Cannot add server to known hosts");

    case SSH_KNOWN_HOSTS_ERROR:
        throw std::runtime_error("Error while verifying host");

    default:
        throw std::runtime_error("Unkonwn case");
    }
}
