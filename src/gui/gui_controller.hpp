#pragma once

#include "../graphics/glcontroller.hpp"
#include "../serializable/config_manager.hpp"
#include "../serializable/blood_cells_definition.hpp"
#include "../vein/nodes/node.hpp"
#include "../bloodcell/blood_editor.hpp"
#include <imgui/imgui/imgui.h>
#include <vector>

namespace gui
{
	enum class Mode
	{
		mainScreen,
		generalEdit,
		bloodEdit,
		veinEdit,
		addVein,
		simulation,
		configureBloodCellSprings, 
		configureBloodCellVertices
	};

	class GUIController
	{
	public:
		GUIController(GLFWwindow* window, serializable::ConfigManager& configManager, graphics::GLController& glController);
		void renderUI();

		void setMode(Mode mode);
		void selectNode(vein::Node* node, bool selectedLeft = true);
		inline void releaseEditor() { selectedEditor = nullptr; }
	private:
		ImGuiIO& io;
		
		Mode mode = Mode::mainScreen;
		serializable::ConfigManager& configManager;
		graphics::GLController& glController;	

		// vein
		bool selectedLeft = true;
		bool firstRender = true;
		vein::Node* selectedNode = configManager.getData().veinDefinition.rootNode.get();

		// blood cells
		std::vector<BloodEditor> editors;
		BloodEditor* selectedEditor = nullptr;

		void finalDraw();
		void loadEditors();

		// Components
		void renderMainScreen();
		void renderGeneralEditor();
		void renderBloodList();
		void renderVeinEditor();
		void renderAddVein();
		void renderSimulation();
		void renderBloodCellSpringsDetails();
		void renderBloodCellVerticesDetails();
	};
}