#include "stream_receiver.hpp"

#include <stdexcept>
#include <iostream>


StreamReceiver::StreamReceiver():
	streamEnd(false)
{
    /* init GStreamer */
	gst_init (NULL, NULL);

    pipeline = gst_pipeline_new("pipeline");
	udpsrc = gst_element_factory_make("udpsrc", "udpsrc");
	capsfilter = gst_element_factory_make("capsfilter", "capsfilter");
	rtpjitterbuffer = gst_element_factory_make("rtpjitterbuffer", "rtpjitterbuffer");
	rtph264depay = gst_element_factory_make("rtph264depay", NULL);
	h264decoder = gst_element_factory_make("avdec_h264", NULL);
	converter = gst_element_factory_make("videoconvert", "converter");
	videosink = gst_element_factory_make("autovideosink", "autovideosink");

	if (!pipeline || !udpsrc || !capsfilter || !rtpjitterbuffer || !rtph264depay || !h264decoder || !converter || !videosink) {
		throw std::runtime_error("Error while creating pipeline object");
	}

	gst_bin_add_many(GST_BIN(pipeline), udpsrc, capsfilter, rtpjitterbuffer, rtph264depay, h264decoder, converter, videosink, NULL);

	if ( !gst_element_link_many(udpsrc, capsfilter, rtpjitterbuffer, rtph264depay, h264decoder, converter, videosink, NULL)) {
		throw std::runtime_error("Cannot link objects to pipeline");
	}

    GstCaps *caps = gst_caps_from_string("application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264, payload=(int)96");
	g_object_set(capsfilter, "caps", caps, NULL);

    bus = gst_element_get_bus(pipeline);
    if (!bus) {
        gst_object_unref(pipeline);
		throw std::runtime_error("Cannot get a pipeline bus");
    }
}


StreamReceiver::~StreamReceiver()
{
    gst_object_unref(bus);
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (GST_OBJECT (pipeline));
	gst_deinit();
}


void StreamReceiver::portSet(int port)
{
    g_object_set(udpsrc, "port", port, NULL);
}


void StreamReceiver::startListening()
{
    GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);

	if (ret == GST_STATE_CHANGE_FAILURE) {
        gst_object_unref(pipeline);
        throw std::runtime_error("Cannot set pipeline to playing state");
    }
}


void StreamReceiver::pause()
{
    GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PAUSED);

	if (ret == GST_STATE_CHANGE_FAILURE) {
        gst_object_unref(pipeline);
        throw std::runtime_error("Cannot set pipeline to playing state");
    }
}

void StreamReceiver::renderFrame()
{
	g_main_context_iteration(g_main_context_default(),FALSE);
}

bool StreamReceiver::streamEnded()
{
    return streamEnd;
}


static void pipelineError(GstMessage* msg)
{
	GError *err;
	gchar *debugTmp;

	gst_message_parse_error(msg, &err, &debugTmp);

	std::string errorSrc(GST_OBJECT_NAME(msg->src));
	std::string debugInfo(debugTmp);
	std::string errorMsg(err->message);

	g_error_free (err);
	g_free (debugTmp);

	throw std::runtime_error(
		"Stream receiver pipeline error."
		" Source: " + errorSrc +
		" Error message: " + errorSrc + 
		" Debug info: " + debugInfo
	);
}


void StreamReceiver::handleEvents()
{
	GstMessage *msg = gst_bus_pop_filtered(bus, static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

	if (msg == NULL) {
		return;
	}

	switch (GST_MESSAGE_TYPE(msg))
	{
	case GST_MESSAGE_ERROR:
		pipelineError(msg);
		break;

	case GST_MESSAGE_EOS:
		streamEnd = true;
		break;

	default:
		throw std::runtime_error("Unexpected message");
	}
}
