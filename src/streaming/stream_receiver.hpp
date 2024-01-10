#pragma once

#include <gst/gst.h>

#include "stream_frame.hpp"

#include <memory>


namespace streaming
{
    class StreamReceiver
    {
    public:
        StreamReceiver();
        ~StreamReceiver();

        void portSet(int port);

        void startListening();
        void pause();

        std::shared_ptr<StreamFrame> getFrame();

        inline bool streamEnded() const { return streamEnd; }

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
