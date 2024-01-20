#pragma once

#include "camera.hpp"
#include "inputcontroller.hpp"
#include "light.hpp"
#include "../serializable/blood_cell_json_conversion/blood_cells_definition.hpp"
#include "../serializable/config_manager.hpp"
#include "../vein/nodes/bifurcation_node.hpp"
#include "../streaming/stream_manager.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <optional>
#include "../vein/vein_mesh.hpp"


/// <summary>
/// This namespace contains all elements responsible for rendering in the OpenGl window
/// </summary>
namespace graphics
{
	/// <summary>
	/// Drawing mode specifies which elements should be drawn in the OpenGL window
	/// </summary>
	enum class Mode
	{
		None,
		Simulation,
		VeinEdit,
	};


	/// <summary>
	/// Controls rendering in the OpenGl window
	/// </summary>
	class GLController {
	public:
		GLController(
			GLFWwindow* window,
			serializable::ConfigManager& configManager,
			streaming::StreamManager& streamManager
		);

		/// <summary>
		/// Draws the specified elements based on which mode is set
		/// </summary>
		void draw();

		/// <summary>
		/// Gets keyboard input from user and processes it
		/// </summary>
		void handleInput();

		/// <summary>
		/// Sets the current drawing mode
		/// </summary>
		/// <param name="mode">Enum specifies which elements should be drawn</param>
		void setMode(Mode mode);
		void setFinalMesh(vein::SerializableMesh& calculatedMesh);

	private:

		Mode mode = Mode::None;

		GLFWwindow* window;

		// Uniform matrices
		glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		glm::mat4 projection = glm::perspective(glm::radians<float>(45.0f), static_cast<float>(windowWidth) / windowHeight, 0.1f, depth * 100);

		InputController inputController;
		
		GLuint streamTex, streamFBO;

		serializable::ConfigManager& configManager;
		streaming::StreamManager& streamManager;

		vein::Node* veinRoot;
		std::unique_ptr<vein::VeinMesh> finalMesh;

		Camera camera;
		bool useLighting = true;
		DirLight directionalLight;
		std::unique_ptr<Shader> veinSolidColorShader;

		unsigned int gBuffer;


		/// <summary>
		/// Draws background only
		/// </summary>
		void drawNothing();

		/// <summary>
		/// Draws the data streamed from the server
		/// </summary>
		void drawSimulation();

		/// <summary>
		/// Draws the vein model in its raw form - every segment is treated as a separate mesh
		/// </summary>
		void drawVeinEditor();

		/// <summary>
		/// Begins listening for data from the server and sets up stream receiving
		/// </summary>
		void beginSimulation();

		/// <summary>
		/// Ends connection to the server
		/// </summary>
		void endSimulation();
	};
}