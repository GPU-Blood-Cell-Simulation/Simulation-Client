#include "stream_receiver.hpp"

#include <gst/app/app.h>

#include <stdexcept>
#include <iostream>


streaming::StreamReceiver::StreamReceiver():
	streamEnd(false)
{
    /* init GStreamer */
	gst_init (NULL, NULL);

    pipeline = gst_pipeline_new("pipeline");
	udpsrc = gst_element_factory_make("udpsrc", "udpsrc");
	capsfilter = gst_element_factory_make("capsfilter", "capsfilter");
	rtpjitterbuffer = gst_element_factory_make("rtpjitterbuffer", "rtpjitterbuffer");
	rtph264depay = gst_element_factory_make("rtph264depay", "rtph264depay");
	h264decoder = gst_element_factory_make("avdec_h264", "avdec_h264");
	converter = gst_element_factory_make("videoconvert", "converter");
	appsink = gst_element_factory_make("appsink", "appsink");

	if (!pipeline || !udpsrc || !capsfilter || !rtpjitterbuffer ||
		!rtph264depay || !h264decoder || !converter || !appsink) {
		throw std::runtime_error("Error while creating pipeline object");
	}

	gst_bin_add_many(GST_BIN(pipeline), udpsrc, capsfilter, rtpjitterbuffer,
		rtph264depay, h264decoder, converter, appsink, NULL);

	if ( !gst_element_link_many(udpsrc, capsfilter, rtpjitterbuffer, rtph264depay,
		h264decoder, converter, appsink, NULL)) {
		throw std::runtime_error("Cannot link objects to pipeline");
	}

    GstCaps *caps = gst_caps_from_string("application/x-rtp, media=(string)video, "
		"clock-rate=(int)90000, encoding-name=(string)H264, payload=(int)96");
	g_object_set(capsfilter, "caps", caps, NULL);
	gst_caps_unref(caps);

	g_object_set(G_OBJECT(rtpjitterbuffer), "latency", 50, NULL);

	caps = gst_caps_new_simple("video/x-raw",
								"format", G_TYPE_STRING, "RGB",
								NULL);
	
	g_object_set(appsink, "caps", caps, NULL);
	gst_caps_unref(caps);

    bus = gst_element_get_bus(pipeline);
    if (!bus) {
        gst_object_unref(pipeline);
		throw std::runtime_error("Cannot get a pipeline bus");
    }

	actFrame = std::make_shared<StreamFrame>(nullptr);
}


streaming::StreamReceiver::~StreamReceiver()
{
    gst_object_unref(bus);
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (GST_OBJECT (pipeline));
	gst_deinit();
}


void streaming::StreamReceiver::portSet(int port)
{
    g_object_set(udpsrc, "port", port, NULL);
}


void streaming::StreamReceiver::startListening()
{
    GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);

	if (ret == GST_STATE_CHANGE_FAILURE) {
        gst_object_unref(pipeline);
        throw std::runtime_error("Cannot set pipeline to playing state");
    }
}


void streaming::StreamReceiver::pause()
{
    GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PAUSED);

	if (ret == GST_STATE_CHANGE_FAILURE) {
        gst_object_unref(pipeline);
        throw std::runtime_error("Cannot set pipeline to playing state");
    }
}

std::shared_ptr<streaming::StreamFrame> streaming::StreamReceiver::getFrame()
{
	GstSample *videosample =
            gst_app_sink_try_pull_sample(GST_APP_SINK(appsink), 10 * GST_MSECOND);

	if (videosample != NULL) {
		actFrame.reset(new StreamFrame(videosample));
	}

	return actFrame;
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


void streaming::StreamReceiver::handleEvents()
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
