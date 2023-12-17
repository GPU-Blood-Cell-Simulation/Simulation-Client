#pragma once

#include <gst/gst.h>

#include "stream_frame.hpp"


class StreamReceiver
{
public:
    StreamReceiver(int frameWidth, int frameHeight);
    ~StreamReceiver();

    void portSet(int port);

    void startListening();
    void pause();

    StreamFrame nextFrame();

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
};
