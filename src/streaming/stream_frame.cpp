#include "stream_frame.hpp"


StreamFrame::StreamFrame(GstSample *sample):
    sample(sample)
{
    if (!haveData()) {
        return;
    }

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
