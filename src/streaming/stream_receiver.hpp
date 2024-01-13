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
        GstElement *tcpsrc;
        GstElement *demuxer;
        GstElement *h264decoder;
        GstElement *converter;
        GstElement *appsink;

        GstBus *bus;

        bool streamEnd;

        std::shared_ptr<StreamFrame> actFrame;

        static GstElement *createPipelineElement(const std::string& factoryName, const std::string& name);
        static void padAddedCallbackHandler(GstElement *src, GstPad *new_pad, streaming::StreamReceiver *data);
    };
}
