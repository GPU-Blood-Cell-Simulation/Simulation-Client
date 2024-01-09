#include <glad/glad.h>

#include "glcontroller.hpp"

#include "../serializable/config_data.hpp"
#include "../defines.hpp"
#include "stream_input_controller.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <memory>


namespace graphics
{
	using namespace glm;

	GLController::GLController(GLFWwindow* window, serializable::ConfigManager& configManager) : window(window), configManager(configManager)
	{
		// Set up GLFW to work with inputController
		glfwSetWindowUserPointer(window, &inputController);
		glfwSetKeyCallback(window, InputController::handleUserInput);

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
		mode = Mode::Simulation;

		streamReceiver.portSet(4321);
		streamReceiver.startListening();

		glGenTextures(1, &streamTex);
		glBindTexture(GL_TEXTURE_2D, streamTex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glGenFramebuffers(1, &streamFBO);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, streamFBO);

		serverCommunication.connectToServer(4322);

		SimulationInputController controller;
		controller.setInputCallback(window, &serverCommunication);
	}

    void GLController::abortSimulation()
    {
		serverCommunication.sendSingleEvent(EventType::stopRendering);
    }

    void GLController::endSimulation()
	{
		mode = Mode::None;

		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &streamTex);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glDeleteFramebuffers(1, &streamFBO);

		streamReceiver.pause();

		serverCommunication.disconnect();

		glfwSetWindowUserPointer(window, &inputController);
		glfwSetKeyCallback(window, InputController::handleUserInput);
	}


	void GLController::handleInput()
	{
		if (mode == Mode::Simulation) {
			serverCommunication.pollEvents();
		}
		else {
			inputController.adjustParametersUsingInput(camera);
		}		
	}


	void GLController::setMode(Mode mode)
	{
		this->mode = mode;
	}

	void GLController::setFinalMesh(vein::SerializableMesh& calculatedMesh)
	{
		finalMesh = std::make_unique<vein::VeinMesh>(std::move(calculatedMesh.positions), std::move(calculatedMesh.indices));
		finalMesh->setupMesh();
	}
	

    void GLController::drawNothing()
	{

	}


	void GLController::drawSimulation()
	{
		streamReceiver.handleEvents();
		
		if (streamReceiver.streamEnded()) {
			endSimulation();
			return;
		}

		std::shared_ptr<StreamFrame> frame(streamReceiver.getFrame());

		if (!frame->haveData()) {
			return;
		}

		int windowWidth;
		int windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frame->getWidth(), frame->getHeight(),
						0, GL_RGBA, GL_UNSIGNED_BYTE, frame->getData());

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