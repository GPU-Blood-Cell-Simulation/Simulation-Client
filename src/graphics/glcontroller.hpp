#pragma once

#include "camera.hpp"
#include "inputcontroller.hpp"
#include "light.hpp"
#include "models/model.hpp"
#include "../serializable/blood_cells_definition.hpp"
#include "../serializable/vein_definition.hpp"
#include "../simulation/simulation_instance.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <optional>


namespace graphics
{
	/// <summary>
	/// Mode that the GLController operates in - what is currently displayed is dependent on this enum
	/// </summary>
	enum class Mode
	{
		None,
		Simulation,
		VeinEdition
	};

	/// <summary>
	/// Controls rendering of blood cellls and the vein
	/// </summary>
	class GLController {
	public:
		GLController(GLFWwindow* window);
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

		// Particle color
		glm::vec3 particleDiffuse = glm::vec3(0.8f, 0.2f, 0.2f);
		float particleSpecular = 0.6f;

		// Uniform matrices
		glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		glm::mat4 projection = glm::perspective(glm::radians<float>(45.0f), static_cast<float>(windowWidth) / windowHeight, 0.1f, depth * 10);

		InputController inputController;
		std::optional<sim::SimulationInstance> simulationInstance;

		Camera camera;

		bool useLighting = true;
		DirLight directionalLight;

		std::unique_ptr<Shader> solidColorShader;
		std::unique_ptr<Shader> geometryPassShader;
		std::unique_ptr<Shader> phongDeferredShader;
		std::unique_ptr<Shader> phongForwardShader;
		std::unique_ptr<Shader> cylinderSolidColorShader;
		std::unique_ptr<Shader> springShader;

		unsigned int gBuffer;
	};
}