#pragma once

#include <gst/gst.h>

#include "stream_frame.hpp"

#include <memory>


namespace streaming
{
    /// <summary>
    /// Receives stream
    /// </summary>
    class StreamReceiver
    {
    public:
        StreamReceiver();
        ~StreamReceiver();

        /// <summary>
        /// Sets port, which client uses to listen video stream
        /// </summary>
        /// <param name="port">Port used for data receiving</param>
        void portSet(int port);

        /// <summary>
        /// Starts listening to stream. Before invocation port must be set
        /// </summary>
        void startListening();

        /// <summary>
        /// Stops listening to stream
        /// </summary>
        void pause();

        /// <summary>
        /// Returns the newest frame, which was received from server
        /// </summary>
        /// <returns>Pointer to newest frame</returns>
        std::shared_ptr<StreamFrame> getFrame();

        /// <summary>
        /// Checks if server ended stream
        /// </summary>
        /// <returns>True if server ended stream</returns>
        inline bool streamEnded() const { return streamEnd; }

        /// <summary>
        /// Function handles all events connected with stream.
        /// Function should be invoked regularly
        /// </summary>
        void handleEvents();

    private:
        GstElement *pipeline;
        GstElement *udpsrc;
        GstElement *capsfilter;
        GstElement *rtpjitterbuffer;
        GstElement *rtph264depay;
        GstElement *h264decoder;
        GstElement *converter;
        GstElement *appsink;

        GstBus *bus;

        bool streamEnd;

        std::shared_ptr<StreamFrame> actFrame;
    };
}
