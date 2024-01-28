#pragma once

#include <enet/enet.h>

#include <cstdint>
#include <string>


/// <summary>
/// Data structure of a single event
/// </summary>
typedef std::uint8_t event_t;


/// <summary>
/// Enum for distinct event types
/// </summary>
enum class EventType: event_t {
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

    togglePolygonMode,
    toggleSpringsRendering,
    toggleSpheresRendering,

    streamSuccessfullyEnded,
    stopRendering,

    newConnection,
    peerDisconnected,

    invalidMessage,
};


class ClientCommunicationEndpoint {
public:
    ClientCommunicationEndpoint();
    ~ClientCommunicationEndpoint();

    void connectToServer(int server_port, const std::string& server_address = "localhost");
    void disconnect();

    void sendStartEvent(EventType event) const;
    void sendEndEvent(EventType event) const;
    void sendSingleEvent(EventType event) const;
    
    EventType pollEvents();
    bool isConnected() const;

private:
    /// <summary>
	/// Number of instances of this class
	/// </summary>
    static int instances;

    ENetPeer* peer;
    ENetHost* client;

    void sendMsg(event_t msg) const;

    static EventType parseEvent(const ENetEvent* event);
    static bool eventIsImportant(EventType event);
};
