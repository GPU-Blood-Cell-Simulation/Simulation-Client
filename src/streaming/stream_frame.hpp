#pragma once

#include <gst/gst.h>

#include <cstdint>


class StreamFrame
{
public:
    StreamFrame(GstSample *sample);
    ~StreamFrame();

    inline bool haveData() const { return sample != NULL; }

    inline uint8_t* getData() const { return map.data; }

    int getWidth();
    int getHeight();

private:
    GstSample *sample;
    GstBuffer *buffer;
    GstMapInfo map;
    GstCaps* cap;
    const GstStructure* structure;
};
