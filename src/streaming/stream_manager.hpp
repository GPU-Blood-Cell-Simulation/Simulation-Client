#pragma once

#include <string>
#include <memory>

#include "stream_receiver.hpp"
#include "stream_frame.hpp"
#include "stream_input_controller.hpp"
#include "../communication/client_endpoint.hpp"


namespace streaming
{
    enum class StreamStatus
    {
        initStatus,
        waitingForServer,
        inProgress,
        successfullyEnded,
        connectionLost
    };


    class StreamManager {
    public:
        StreamManager();

        void setupInputCallback(GLFWwindow* window);
        void beginWatchingSimulation(int streamPort, int communicationPort, const std::string& address = "localhost");

        void endWatchingSimulation();

        void abortSimulation();

        StreamStatus streamStatusGet() const;
        std::shared_ptr<StreamFrame> streamFrameGet();

        void handleInput();

    private:
        StreamStatus streamStatus;

        StreamReceiver streamReceiver;
        ClientCommunicationEndpoint serverCommunication;
        SimulationInputController inputController;

        
    };
}
