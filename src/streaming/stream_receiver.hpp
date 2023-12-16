#pragma once

#include <gst/gst.h>


class StreamReceiver
{
public:
    StreamReceiver();
    ~StreamReceiver();

    void portSet(int port);

    void startListening();
    void pause();

    void renderFrame();

    bool streamEnded();

    void handleEvents();

private:
    GstElement *pipeline;
    GstElement *udpsrc;
    GstElement *capsfilter;
    GstElement *rtpjitterbuffer;
    GstElement *rtph264depay;
    GstElement *h264decoder;
    GstElement *converter;
    GstElement *videosink;

    GstBus *bus;

    bool streamEnd;
};
