#pragma once

#include <string>
#include <memory>

#include "stream_receiver.hpp"
#include "stream_frame.hpp"
#include "stream_input_controller.hpp"
#include "../communication/client_endpoint.hpp"


namespace streaming
{
    /// <summary>
    /// Enum, which contains possible stream statuses
    /// </summary>
    enum class StreamStatus
    {
        initStatus,
        waitingForServer,
        inProgress,
        successfullyEnded,
        connectionLost
    };


    /// <summary>
    /// Aggregates stream receiving to sending into single, simpler interface
    /// </summary>
    class StreamManager {
    public:
        StreamManager();

        /// <summary>
        /// Sets callback which send messages to server according to user keyboard actions
        /// </summary>
        /// <param name="window">Pointer to GLFW window with stream output</param>
        void setupInputCallback(GLFWwindow* window);

        /// <summary>
        /// Starts receiving video frames from server
        /// </summary>
        /// <param name="streamPort">Port which server uses to stream video</param>
        /// <param name="communicationPort">Port which server uses to send events to client</param>
        /// <param name="address">Server network address</param>
        void beginWatchingSimulation(int streamPort, int communicationPort, const std::string& address = "localhost");

        /// <summary>
        /// Finishes receiving stream from client. Simulation on server is not stopped
        /// </summary>
        void endWatchingSimulation();

        /// <summary>
        /// Sends event to server, which requests simulation stop
        /// </summary>
        void abortSimulation();

        /// <summary>
        /// Returns actual stream status
        /// </summary>
        /// <returns>Stream status</returns>
        StreamStatus streamStatusGet() const;

        /// <summary>
        /// Returns the newest frame received from server.
        /// If client is not connected or no frames was received, then returned
        /// frames have not data - for ore information refer to StreamFrame class documentation.
        /// Subsequent calls can return the same frame.
        /// </summary>
        /// <returns>Pointer to the newest StreamFrame</returns>
        std::shared_ptr<StreamFrame> streamFrameGet();

        /// <summary>
        /// Handles events connected with sending messages and receiving stream.
        /// This function should be called on every frame.
        /// </summary>
        void handleInput();

    private:
        /// <summary>
        /// Actual status of the stream
        /// </summary>
        StreamStatus streamStatus;

        /// <summary>
        /// Object responsible for stream receiving
        /// </summary>
        StreamReceiver streamReceiver;

        /// <summary>
        /// Object responsible for handling communication
        /// </summary>
        ClientCommunicationEndpoint serverCommunication;

        /// <summary>
        /// Object responsible for handling input from user
        /// </summary>
        SimulationInputController inputController;
    };
}
