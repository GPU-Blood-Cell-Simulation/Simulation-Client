#include "client_endpoint.hpp"

#include <stdexcept>
#include <iostream>


#define BITS_IN_BYTE 8
#define START_EVENT_MASK (event_t)(1 << (sizeof(event_t) * BITS_IN_BYTE - 1))
#define EVENT_PAYLOAD (~START_EVENT_MASK)

#define NUMBER_OF_CHANNELS 2
#define STD_CHANNEL_ID 0
#define IMPORTANT_CHANNEL_ID 1


int ClientCommunicationEndpoint::instances = 0;


ClientCommunicationEndpoint::ClientCommunicationEndpoint():
    peer(NULL)
{
    if (instances++ == 0) {
        if (enet_initialize() != 0) {
            throw std::runtime_error("Cannot initialize message receiver");
        }
    }

    client = enet_host_create (
        NULL,                // Create a client host
        1,                   // Max number of clients
        NUMBER_OF_CHANNELS,
        0,                   // Accept any amount of incoming bandwidth
        0                    // Accept any amount of outgoing bandwidth
    );

    if (client == NULL) {
        throw std::runtime_error("Cannot create a host");
    }
}


ClientCommunicationEndpoint::~ClientCommunicationEndpoint()
{
    enet_host_destroy(client);

    if (--instances == 0) {
        enet_deinitialize();
    }
}


void ClientCommunicationEndpoint::connectToServer(int server_port, const std::string &server_address)
{
    ENetAddress address;

    if (enet_address_set_host(&address, server_address.c_str()) < 0) {
        throw std::runtime_error("Error while setting host");
    }

    address.port = server_port;

    peer = enet_host_connect(client, &address, NUMBER_OF_CHANNELS, 0);
    if (peer == NULL) {
        throw std::runtime_error("Error while establishing connection");
    }
}


void ClientCommunicationEndpoint::disconnect()
{
    ENetEvent event;
    bool successful_disconnect = false;

    if (!isConnected()) {
        return;
    }

    enet_peer_disconnect(peer, 0);

    // Wait for three seconds for peer response
    while (enet_host_service(client, &event, 3000) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy (event.packet);
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            successful_disconnect = true;
            return;

        default:
            break;
        }
    }

    if (!successful_disconnect) {
        enet_peer_reset(peer);
    }
}


void ClientCommunicationEndpoint::sendStartEvent(EventType event) const
{
    if (!eventSupportDuration(event))
        throw std::runtime_error("Event is not supporting duration");

    sendMsg(static_cast<event_t>(event) | START_EVENT_MASK);
}


void ClientCommunicationEndpoint::sendEndEvent(EventType event) const
{
    if (!eventSupportDuration(event))
        throw std::runtime_error("Event is not supporting duration");

    sendMsg((static_cast<event_t>(event)));
}


void ClientCommunicationEndpoint::sendSingleEvent(EventType event) const
{
    if (eventSupportDuration(event))
        throw std::runtime_error("Event is cannot supporting duration");

    sendMsg((static_cast<event_t>(event)));
}


EventType ClientCommunicationEndpoint::pollEvents()
{
    ENetEvent event;
    EventType result;

    if (enet_host_service(client, &event, 0) < 0) {
        throw std::runtime_error("Error while polling messages");
    }

    switch (event.type)
    {
    case ENET_EVENT_TYPE_RECEIVE:
        result = parseEvent(&event);
        enet_packet_destroy(event.packet);
        return result;

    case ENET_EVENT_TYPE_NONE:
        return EventType::noMessage;

    case ENET_EVENT_TYPE_CONNECT:
        return EventType::newConnection;

    case ENET_EVENT_TYPE_DISCONNECT:
        return EventType::peerDisconnected;
    
    default:
        throw std::runtime_error("Undefined message type");
    }
}


bool ClientCommunicationEndpoint::isConnected() const
{
    if (peer->state == ENET_PEER_STATE_CONNECTED) {
        return true;
    }

    return false;
}


void ClientCommunicationEndpoint::sendMsg(event_t event) const
{
    if (!isConnected()) {
        return;
    }

    ENetPacket* packet = enet_packet_create(&event, sizeof(event_t), ENET_PACKET_FLAG_RELIABLE);
    if (packet == NULL) {
        throw std::runtime_error("Error while creating a packet");
    }

    enet_uint8 channel = eventIsImportant((EventType)event) ? IMPORTANT_CHANNEL_ID : STD_CHANNEL_ID;

    if (enet_peer_send(peer, channel, packet) != 0) {
        throw std::runtime_error("Error while sending a packet");
    }
}


EventType ClientCommunicationEndpoint::parseEvent(const ENetEvent *event)
{
    static_assert((event_t)EventType::invalidMessage < START_EVENT_MASK);

    if (event->packet->dataLength != sizeof(EventType)) {
        return EventType::invalidMessage;
    }

    return static_cast<EventType>(*event->packet->data & EVENT_PAYLOAD);
}


bool ClientCommunicationEndpoint::eventIsImportant(EventType event)
{
    switch (event)
    {
    case EventType::streamSuccessfullyEnded:
    case EventType::stopRendering:
        return true;
    
    default:
        return false;
    }
}


bool ClientCommunicationEndpoint::eventSupportDuration(EventType event)
{
    int eventCode = static_cast<int>(event);


    if (eventCode >= static_cast<int>(EventType::cameraLeft) &&
        eventCode <= static_cast<int>(EventType::cameraRotateDown))
        return true;

    return false;
}
