#include "stream_manager.hpp"


streaming::StreamManager::StreamManager():
    streamStatus(StreamStatus::initStatus),
    streamReceiver(),
    serverCommunication()
{ }


void streaming::StreamManager::setupInputCallback(GLFWwindow *window)
{
    inputController.setInputCallback(window, &serverCommunication);
}


void streaming::StreamManager::beginWatchingSimulation(int streamPort, int communicationPort, const std::string &address)
{
    streamReceiver.portSet(streamPort);
	streamReceiver.startListening();

    serverCommunication.connectToServer(communicationPort, address);

    streamStatus = StreamStatus::waitingForServer;
}


void streaming::StreamManager::endWatchingSimulation()
{
    if (streamStatus == StreamStatus::initStatus) {
        return;
    }

    streamReceiver.pause();

    serverCommunication.disconnect();

    streamStatus = StreamStatus::initStatus;
}


void streaming::StreamManager::abortSimulation()
{
    serverCommunication.sendSingleEvent(EventType::stopRendering);
}


streaming::StreamStatus streaming::StreamManager::streamStatusGet() const
{
    return streamStatus;
}


std::shared_ptr<streaming::StreamFrame> streaming::StreamManager::streamFrameGet()
{
    streamReceiver.handleEvents();
    if (streamReceiver.streamEnded()) {
        streamStatus = StreamStatus::connectionLost;
    }

    return streamReceiver.getFrame();
}

void streaming::StreamManager::handleInput()
{
    EventType event = serverCommunication.pollEvents();

    switch (event)
    {
    case EventType::streamSuccessfullyEnded:
        streamStatus = StreamStatus::successfullyEnded;
        break;

    case EventType::newConnection:
        streamStatus = StreamStatus::inProgress;
        break;

    case EventType::peerDisconnected:
        if (streamStatus != StreamStatus::successfullyEnded)
            streamStatus = StreamStatus::connectionLost;
        break;
    
    default:
        break;
    }
}
