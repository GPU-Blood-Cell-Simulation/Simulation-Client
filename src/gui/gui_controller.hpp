#pragma once

#include "../graphics/glcontroller.hpp"
#include "../serializable/config_manager.hpp"
#include "../serializable/blood_cell_json_conversion/blood_cells_definition.hpp"
#include "../vein/nodes/node.hpp"
#include "../bloodcell/blood_editor.hpp"
#include "../streaming/stream_manager.hpp"
#include <imgui/imgui/imgui.h>
#include <vector>

/// <summary>
/// This namespace contains all classes and functions responsible for rendering the UI and communicating with the user
/// </summary>
namespace gui
{
	/// <summary>
	/// Decides which screen should be displayed in the GUI window
	/// </summary>
	enum class Mode
	{
		mainScreen,
		generalEdit,
		bloodEdit,
		veinEdit,
		addVein,
		selectingRuntimeType,
		localRuntime,
		manualRuntime,
		streamWatching,
		configureBloodCellSprings, 
		configureBloodCellVertices,
		configureBloodCellColor
	};

	/// <summary>
	/// Specifies the IO operation which should be performed after the "Choose file" dialog window is closed successfully
	/// </summary>
	enum class IoOperation
	{
		none,
		generalLoad,
		bloodCellLoad,
		veinLoad,
		generalSave,
		bloodCellSave,
		veinSave
	};

	/// <summary>
	/// Responsible for displaying the GUI in a separate ImGui window.
	/// Handles ImGui initialization, setup and all logic associated with interaction through the graphical interface
	/// </summary>
	class GUIController
	{
	public:
		GUIController(
			GLFWwindow* window,
			serializable::ConfigManager& configManager,
			streaming::StreamManager& streamManager,
			graphics::GLController& glController
		);

		/// <summary>
		/// Renders the whole UI in every frame
		/// </summary>
		void renderUI();

		/// <summary>
		/// Switches which screen should be rendered
		/// </summary>
		void setMode(Mode mode);

		/// <summary>
		/// Select a vein segment node in order to add new children to it
		/// </summary>
		/// <param name="node">A node to select (clicked by user)</param>
		/// <param name="selectedLeft">Whether the selected node is the left child of its parent</param>
		void selectNode(vein::Node* node, bool selectedLeft = true);
		inline void releaseEditor() { selectedEditor = nullptr; }
	private:
		ImGuiIO& io;
		
		Mode mode = Mode::mainScreen;
		serializable::ConfigManager& configManager;
		streaming::StreamManager& streamManager;
		graphics::GLController& glController;	

		// vein
		bool selectedLeft = true;
		bool firstRender = true;
		vein::Node* selectedNode = configManager.getData().veinRootNode.get();

		// blood cells
		std::vector<BloodEditor> editors;
		BloodEditor* selectedEditor = nullptr;

		std::string error;
		void setError(const std::string& msg);

		void finalDraw();
		void loadEditors();
		void addTypeAndEditor(std::string typeName, int typeSize);

		// Components
		void renderMenuBar();
		void renderDialogWindow(IoOperation& operation);

		void renderMainScreen();
		void renderGeneralEditor();
		void renderBloodList(serializable::ConfigData& config);
		void renderVeinEditor();
		void renderAddVein();
		void renderStream();
		void renderManualSimulation();
		void renderSimulationTypeSelect();
		void renderBloodCellSpringsDetails(serializable::ConfigData& config);
		void renderBloodCellVerticesDetails(serializable::ConfigData& config);
		void renderBloodCellColorDetails(serializable::ConfigData& config);
		void renderSimulationEditor();
		void renderPhysicsEditor();
		void renderGraphicsEditor();

#ifndef  _WIN32
		void renderLocalSimulation();
#endif
	};
}