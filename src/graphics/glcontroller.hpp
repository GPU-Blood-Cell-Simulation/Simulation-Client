#pragma once

#include "camera.hpp"
#include "inputcontroller.hpp"
#include "light.hpp"
#include "../serializable/blood_cell_json_conversion/blood_cells_definition.hpp"
#include "../serializable/config_manager.hpp"
#include "../vein/nodes/bifurcation_node.hpp"
#include "../streaming/stream_receiver.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <optional>
#include "../vein/vein_mesh.hpp"


namespace graphics
{
	enum class Mode
	{
		None,
		Simulation,
		VeinEdit,
	};

	// Controls rendering of the particles
	class GLController {
	public:
		GLController(GLFWwindow* window, serializable::ConfigManager& configManager);
		void drawNothing();
		void drawSimulation();
		void drawVeinEditor();
		void draw();
		void beginSimulation();
		void endSimulation();
		void handleInput();
		void setMode(Mode mode);
		void setFinalMesh(vein::SerializableMesh& calculatedMesh);

	private:

		Mode mode = Mode::None;

		GLFWwindow* window;

		// Uniform matrices
		glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		glm::mat4 projection = glm::perspective(glm::radians<float>(45.0f), static_cast<float>(windowWidth) / windowHeight, 0.1f, depth * 100);

		InputController inputController;
		
		StreamReceiver streamReceiver;
		GLuint streamTex, streamFBO;

		serializable::ConfigManager& configManager;

		std::unique_ptr<vein::VeinMesh> finalMesh;

		Camera camera;
		bool useLighting = true;
		DirLight directionalLight;
		std::unique_ptr<Shader> cylinderSolidColorShader;

		unsigned int gBuffer;
	};
}