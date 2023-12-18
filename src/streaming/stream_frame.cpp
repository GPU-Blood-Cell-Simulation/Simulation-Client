#include "stream_frame.hpp"


#include <iostream>

StreamFrame::StreamFrame(GstSample *sample):
    sample(sample)
{
    if (!haveData()) {
        return;
    }

    cap = gst_sample_get_caps(sample);
    structure = gst_caps_get_structure (cap, 0);

    buffer = gst_sample_get_buffer(sample);
    gst_buffer_map(buffer, &map, GST_MAP_READ);
}


StreamFrame::~StreamFrame()
{
    if (!haveData()) {
        return;
    }

    gst_buffer_unmap(buffer, &map);
    gst_sample_unref(sample);
}


int StreamFrame::getWidth()
{
    if (!haveData()) {
        return 0;
    }

    int result;
    gst_structure_get_int(structure, "width", &result);

    std::cout << "Width: " << result << std::endl;

    return result;
}

int StreamFrame::getHeight()
{
    if (!haveData()) {
        return 0;
    }

    int result;
    gst_structure_get_int(structure, "height", &result);

    return result;
}
