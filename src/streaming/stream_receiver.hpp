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

    GstCaps *capsfilter_format(int width, int height);
};
