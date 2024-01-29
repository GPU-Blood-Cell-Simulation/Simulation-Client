#pragma once

#include <enet/enet.h>

#include <cstdint>
#include <string>


/// <summary>
/// Data structure of a single event
/// </summary>
typedef std::uint8_t event_t;


/// <summary>
/// Enum for all supported event types
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

    /// <summary>
    /// Default constructor
    /// </summary>
    ClientCommunicationEndpoint();

    /// <summary>
    /// Class destructor
    /// </summary>
    ~ClientCommunicationEndpoint();

    /// <summary>
    /// Tries to connect to server. Throw exception in case of an error while connecting.
    /// </summary>
    /// <param name="server_port">Port on which server is listening</param>
    /// <param name="server_address">Address on which server is listening</param>
    void connectToServer(int server_port, const std::string& server_address = "localhost");

    /// <summary>
    /// Function disconnects from server. Can be safely executed even if not connected to server.
    /// </summary>  
    void disconnect();

    /// <summary>
    /// Sends an event, which indicates start of an event.
    /// Only camera steering messages can be used. Invalid messages types causes exception.
    /// </summary>
    /// <param name="event">Address on which server is listening</param>
    void sendStartEvent(EventType event) const;

    /// <summary>
    /// Sends an event, which indicates end of an event.
    /// Only camera steering messages can be used. Invalid messages types causes exception.
    /// </summary> 
    void sendEndEvent(EventType event) const;

    /// <summary>
    /// Sends an event, which does not support duration.
    /// Camera steering messages cannot be used with this function. Invalid messages types causes exception.
    /// </summary> 
    void sendSingleEvent(EventType event) const;
    
    /// <summary>
	/// Checks for incoming events from the server. If client received no events, then
    /// returns noMessage event. Function is not blocking.
	/// </summary>
	/// <returns>Event received from the server</returns>
    EventType pollEvents();

    /// <summary>
	/// Checks if client is connected to server
	/// </summary>
	/// <returns>True if client is connected and false if it is not</returns>
    bool isConnected() const;

private:
    /// <summary>
	/// Number of instances of this class
	/// </summary>
    static int instances;

    /// <summary>
	/// Instance of server to which client is connected
	/// </summary>
    ENetPeer* peer;

    /// <summary>
	/// Instance of client endpoint
	/// </summary>
    ENetHost* client;

    /// <summary>
	/// General function to send events to server
	/// </summary>
    void sendMsg(event_t msg) const;

    /// <summary>
	/// Parses event from ENet library format to interface specific.
    /// If event cannot be parsed invalidMessage is returned. 
	/// </summary>
    /// <param name="event">Event received from ENet library</param>
    /// <returns>Parsed event received from client</returns>
    static EventType parseEvent(const ENetEvent* event);

    /// <summary>
	/// Checks if this event should be send using import channel 
	/// </summary>
    /// <param name="event">Event to check</param>
    /// <returns>True if should be send with important channel</returns>
    static bool eventIsImportant(EventType event);

    /// <summary>
	/// Checks if this event can be used with sendStartEvent and sendEndEvent
    /// functions.
	/// </summary>
    /// <param name="event">Event to check</param>
    /// <returns>True if event supports duration</returns>
    static bool eventSupportDuration(EventType event);
};
