#include "stream_frame.hpp"


streaming::StreamFrame::StreamFrame(GstSample *sample):
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


streaming::StreamFrame::~StreamFrame()
{
    if (!haveData()) {
        return;
    }

    gst_buffer_unmap(buffer, &map);
    gst_sample_unref(sample);
}

uint8_t *streaming::StreamFrame::getData() const
{
    if (!haveData()) {
        return NULL;
    }

    return map.data;
}

int streaming::StreamFrame::getWidth()
{
    if (!haveData()) {
        return 0;
    }

    int result;
    gst_structure_get_int(structure, "width", &result);

    return result;
}

int streaming::StreamFrame::getHeight()
{
    if (!haveData()) {
        return 0;
    }

    int result;
    gst_structure_get_int(structure, "height", &result);

    return result;
}
