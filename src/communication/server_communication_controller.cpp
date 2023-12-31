#include "server_communication_controller.hpp"

#include <stdexcept>
#include <iostream>

#define BITS_IN_BYTE 8
#define START_EVENT_MASK (eventType)(1 << (sizeof(eventType) * BITS_IN_BYTE - 1))


ServerCommunicationController::ServerCommunicationController():
    peer(NULL)
{
    if (enet_initialize() != 0) {
        throw std::runtime_error("Cannot initialize message receiver");
    }

    client = enet_host_create (NULL /* create a client host */,
            1 /* only allow 1 outgoing connection */,
            2 /* allow up 2 channels to be used, 0 and 1 */,
            0, 0);

    if (client == NULL) {
        throw std::runtime_error("Cannot create a host");
    }
}


ServerCommunicationController::~ServerCommunicationController()
{
    enet_host_destroy(client);
    enet_deinitialize();
}


void ServerCommunicationController::connectToServer(int server_port, const std::string &server_address)
{
    ENetAddress address;

    if (enet_address_set_host(&address, server_address.c_str()) < 0) {
        throw std::runtime_error("Error while setting host");
    }

    address.port = server_port;

    peer = enet_host_connect(client, &address, 2, 0);
    if (peer == NULL) {
        throw std::runtime_error("Error while establishing connection");
    }
}


void ServerCommunicationController::disconnect()
{
    ENetEvent event;
    bool successful_disconnect = false;

    enet_peer_disconnect(peer, 0);

    while (enet_host_service (client, &event, 3000) > 0)
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


void ServerCommunicationController::sendStartEvent(Event event) const
{
    sendMsg((eventType)event | START_EVENT_MASK);
}


void ServerCommunicationController::sendEndEvent(Event event) const
{
    sendMsg((eventType)event);
}


void ServerCommunicationController::sendMsg(eventType msg) const
{
    if (connectionStateGet() == ConnectionState::disconnected) {
        return;
    }

    ENetPacket* packet = enet_packet_create(&msg, sizeof(eventType), ENET_PACKET_FLAG_RELIABLE);
    if (packet == NULL) {
        throw std::runtime_error("Error while creating a packet");
    }

    if (enet_peer_send(peer, 0, packet) != 0) {
        throw std::runtime_error("Error while sending a packet");
    }
}


Event ServerCommunicationController::pollMessages()
{
    ENetEvent event;
    Event result = Event::noMessage;

    if (enet_host_service(client, &event, 0) < 0) {
        throw std::runtime_error("Error while polling messages");
    }

    switch (event.type)
    {
    case ENET_EVENT_TYPE_RECEIVE:
        /* Client should not receive any messages */
        enet_packet_destroy(event.packet);
        result = Event::invalidMessage;
        break;

    case ENET_EVENT_TYPE_NONE:
    case ENET_EVENT_TYPE_CONNECT:
    case ENET_EVENT_TYPE_DISCONNECT:
        break;
    
    default:
        throw std::runtime_error("Undefined message type");
    }

    return result;
}


ConnectionState ServerCommunicationController::connectionStateGet() const
{
    if (peer->state == ENET_PEER_STATE_CONNECTED) {
        return ConnectionState::connected;
    }

    return ConnectionState::disconnected;
}
