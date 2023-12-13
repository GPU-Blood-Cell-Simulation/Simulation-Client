#pragma once
#define LIBSSH_STATIC 1
#include <libssh/libssh.h>

#include <string>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")


class CommunicationController
{ 
public:
	CommunicationController(
		const std::string& facultyLogin,
		const std::string& facultyPassword,
		const std::string& edenLogin,
		const std::string& edenPassword);

	~CommunicationController();

private:
	std::string facultyHost = "ssh.mini.pw.edu.pl";
	std::string edenHost = "eden.mini.pw.edu.pl";

	ssh_session session;
	ssh_channel channel;

	void verify_host();
};
