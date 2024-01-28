#include <glad/glad.h>

#include "glcontroller.hpp"

#include "../serializable/config_data.hpp"
#include "../defines.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <memory>


namespace graphics
{
	using namespace glm;

	GLController::GLController(GLFWwindow* window, serializable::ConfigManager& configManager, streaming::StreamManager& streamManager):
		window(window), configManager(configManager), streamManager(streamManager)
	{
		inputController.setInputCallback(window);
		glfwSetWindowSizeCallback(window, window_size_callback);

		// Create a directional light
		directionalLight = DirLight
		{
			{
				vec3(0.4f, 0.4f, 0.4f), vec3(1, 1, 1), vec3(1, 1, 1)
			},
			vec3(0, 0, -1.0f)
		};

		// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
		unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, attachments);

		// create and attach depth buffer (renderbuffer)
		unsigned int rboDepth;
		glGenRenderbuffers(1, &rboDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowWidth, windowHeight);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

		// finally check if framebuffer is complete
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Create the shaders
		veinSolidColorShader = std::make_unique<VeinSolidColorShader>();
	}

	void GLController::beginSimulation()
	{
		streamManager.setupInputCallback(window);
		streamManager.beginWatchingSimulation(4321, 4322);

		glGenTextures(1, &streamTex);
		glBindTexture(GL_TEXTURE_2D, streamTex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glGenFramebuffers(1, &streamFBO);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, streamFBO);
	}


    void GLController::endSimulation()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &streamTex);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glDeleteFramebuffers(1, &streamFBO);

		streamManager.endWatchingSimulation();

		// Change user input callback to default
		inputController.setInputCallback(window);
	}


    void GLController::window_size_callback(GLFWwindow *window, int width, int height)
    {
		glViewport(0, 0, width, height);
    }


    void GLController::handleInput()
	{
		switch (mode)
		{
		case Mode::Simulation:
			streamManager.handleInput();
			break;

		case Mode::VeinEdit:
			inputController.adjustParametersUsingInput(camera);
			break;
		
		default:
			break;
		}	
	}


	void GLController::setMode(Mode mode)
	{
		if (this->mode == Mode::Simulation && mode != Mode::Simulation)
			endSimulation();

		this->mode = mode;

		if (mode == Mode::Simulation)
			beginSimulation();
	}
	

    void GLController::drawNothing()
	{

	}


	void GLController::drawSimulation()
	{
		std::shared_ptr<streaming::StreamFrame> frame(streamManager.streamFrameGet());

		if (!frame->haveData()) {
			return;
		}

		int windowWidth;
		int windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame->getWidth(), frame->getHeight(),
						0, GL_RGB, GL_UNSIGNED_BYTE, frame->getData());

		glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                        GL_TEXTURE_2D, streamTex, 0);

        glBlitFramebuffer(0, 0, frame->getWidth(), frame->getHeight(),
                        0, 0, windowWidth, windowHeight,
                        GL_COLOR_BUFFER_BIT, GL_LINEAR);
	}


	void GLController::drawVeinEditor() 
	{
		veinSolidColorShader->use();
		veinSolidColorShader->setMatrix("view", camera.getView());
		veinSolidColorShader->setMatrix("projection", projection);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		configManager.getData().veinRootNode->draw(veinSolidColorShader.get());
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}


	void GLController::draw()
	{
		switch (mode)
		{
		case Mode::None:
			drawNothing();
			break;
		case Mode::Simulation:
			drawSimulation();
			break;
		case Mode::VeinEdit:
			drawVeinEditor();
			break;
		}
	}
}