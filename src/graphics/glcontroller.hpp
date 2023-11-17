#pragma once

#include "camera.hpp"
#include "inputcontroller.hpp"
#include "light.hpp"
#include "../serializable/blood_cells_definition.hpp"
#include "../serializable/vein_definition.hpp"
#include "../serializable/config_data.hpp"
#include "../vein/nodes/bifurcation_node.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <optional>


namespace graphics
{
	enum class Mode
	{
		None,
		Simulation,
		VeinEdition
	};

	// Controls rendering of the particles
	class GLController {
	public:
		GLController(GLFWwindow* window, vein::Node* veinRoot);
		void drawNothing();
		void drawSimulation();
		void drawVeinEditor();
		void draw();
		void beginSimulation(const serializable::ConfigData& configData);
		void endSimulation();
		inline void handleInput()
		{
			inputController.adjustParametersUsingInput(camera);
		}

		Mode mode = Mode::None;

	private:

		// Uniform matrices
		glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		glm::mat4 projection = glm::perspective(glm::radians<float>(45.0f), static_cast<float>(windowWidth) / windowHeight, 0.1f, depth * 10);

		InputController inputController;
		vein::Node* veinRoot;

		Camera camera;

		bool useLighting = true;
		DirLight directionalLight;

		std::unique_ptr<Shader> cylinderSolidColorShader;

		unsigned int gBuffer;
	};
}