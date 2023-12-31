#pragma once

#include <enet/enet.h>

#include <cstdint>
#include <string>


typedef std::uint8_t eventType;

enum class Event: eventType {
    noMessage = 0,

    cameraLeft,
    cameraRight,
    cameraForward,
    cameraBack,
    cameraAscend,
    cameraDescend,

    cameraRotateLeft,
    cameraRotateRight,
    cameraRotateUp,
    cameraRotateDown,

    invalidMessage,
};


enum class ConnectionState {
    connected,
    disconnected
};


class ServerCommunicationController {
public:
    ServerCommunicationController();
    ~ServerCommunicationController();

    void connectToServer(int server_port, const std::string& server_address = "localhost");
    void disconnect();

    void sendStartEvent(Event event) const;
    void sendEndEvent(Event event) const;
    
    Event pollMessages();
    ConnectionState connectionStateGet() const;

private:
    ENetPeer* peer;
    ENetHost* client;

    void sendMsg(eventType msg) const;
};



