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
	if (!pipeline) {
		throw std::runtime_error("Error while creating pipeline object");
	}

	tcpsrc = createPipelineElement("tcpclientsrc", "tcpsrc");
	h264parser = createPipelineElement("h264parse", "h264parser");
	h264decoder = createPipelineElement("avdec_h264", "h264decoder");
	converter = createPipelineElement("videoconvert", "converter");
	appsink = createPipelineElement("appsink", "appsink");

	gst_bin_add_many(GST_BIN(pipeline), tcpsrc, h264parser, h264decoder, converter, appsink, NULL);

	if (gst_element_link_many(tcpsrc, h264parser, h264decoder, converter, appsink, NULL) != TRUE ) {
			throw std::runtime_error("Cannot link objects to pipeline");

	}

	GstCaps *caps = gst_caps_new_simple("video/x-raw",
								"format", G_TYPE_STRING, "RGBA",
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
    g_object_set(tcpsrc, "port", port, NULL);
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

GstElement *streaming::StreamReceiver::createPipelineElement(const std::string &factoryName, const std::string &name)
{
    GstElement *result = gst_element_factory_make(factoryName.c_str(), name.c_str());
	if (!result) {
		throw std::runtime_error("Error while creating " + name + " element");
	}

	return result;
}
