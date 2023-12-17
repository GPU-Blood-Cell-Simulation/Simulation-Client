#include <glad/glad.h>

#include "glcontroller.hpp"

#include "../serializable/config_data.hpp"
#include "../defines.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>


namespace graphics
{

	GLController::GLController(GLFWwindow* window, vein::Node* veinRoot) : streamReceiver(800, 800), veinRoot(veinRoot)
	{
		clearScreen();

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
		cylinderSolidColorShader = std::make_unique<Shader>(CylinderSolidColorShader());
	}


	void GLController::beginSimulation(/*const serializable::ConfigData& configData*/)
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

		std::cout << "Simulation begun\n";
	}

	void GLController::endSimulation()
	{
		mode = Mode::None;

		std::cout << "Simulation ended\n";
	}


	void GLController::handleInput()
	{
		inputController.adjustParametersUsingInput(camera);
	}


	void GLController::setMode(Mode mode)
	{
		this->mode = mode;

		if (mode == Mode::Simulation) {
			beginSimulation();
		}
	}

	void GLController::setFinalMesh(vein::SerializableMesh& calculatedMesh)
	{
		finalMesh = std::make_unique<vein::VeinMesh>(std::move(calculatedMesh.positions), std::move(calculatedMesh.indices));
		finalMesh->setupMesh();
	}

    void GLController::clearScreen()
    {
		// Clear 
        glClearColor(1.00f, 0.75f, 0.80f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLController::drawNothing()
	{
		clearScreen();
	}


	void GLController::drawSimulation()
	{
		streamReceiver.handleEvents();
		
		if (streamReceiver.streamEnded()) {
			streamReceiver.pause();
			endSimulation();
			return;
		}

		StreamFrame frame = streamReceiver.nextFrame();

		if (!frame.haveData()) {
			return;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 800, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame.getData());

		glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                            GL_TEXTURE_2D, streamTex, 0);
        glBlitFramebuffer(0, 0, 800, 800,
                        0, 0, 800, 800,
                        GL_COLOR_BUFFER_BIT, GL_LINEAR);
	}


	void GLController::drawVeinEditor() 
	{
		clearScreen();

		cylinderSolidColorShader->use();
		cylinderSolidColorShader->setMatrix("view", camera.getView());
		cylinderSolidColorShader->setMatrix("projection", projection);

		glDisable(GL_CULL_FACE);
		veinRoot->draw(cylinderSolidColorShader.get());
		glEnable(GL_CULL_FACE);
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