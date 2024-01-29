#pragma once

#include <gst/gst.h>

#include <cstdint>


namespace streaming
{
    /// <summary>
	/// Class represents single video frame received from server
	/// </summary>
    class StreamFrame
    {
    public:
        StreamFrame(GstSample *sample);
        ~StreamFrame();

        /// <summary>
        /// If no frames were received from server, then frames without data are returned
        /// </summary>
        /// <returns>True if frame contains full video frame</returns>
        inline bool haveData() const { return sample != NULL; }

        /// <summary>
        /// Allows to get raw RGB pixel data of single video frame.
        /// Single pixels is described by three bytes - one for each channel.
        /// </summary>
        /// <returns>Pointer to frame data or NULL if frame have no data</returns>
        uint8_t* getData() const;

        /// <summary>
        /// Returns width of video frame
        /// </summary>
        /// <returns>Width of video frame or 0 if frame have no data</returns>
        int getWidth();

        /// <summary>
        /// Returns height of video frame
        /// </summary>
        /// <returns>Height of video frame or 0 if frame have no data</returns>
        int getHeight();

    private:
        GstSample *sample;
        GstBuffer *buffer;
        GstMapInfo map;
        GstCaps* cap;
        const GstStructure* structure;
    };
}
