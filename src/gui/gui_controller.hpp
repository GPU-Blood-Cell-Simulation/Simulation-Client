#pragma once

#include "../graphics/glcontroller.hpp"
#include "../serializable/config_manager.hpp"
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
		GUIController(GLFWwindow* window, graphics::GLController& glController, serializable::ConfigManager& configManager, vein::Node* rootNode);
		void renderUI();

		void setMode(Mode mode);
		void selectNode(vein::Node* node, bool selectedLeft = true);
		void releaseEditor() { selectedEditor = nullptr; }
	private:
		ImGuiIO& io;
		
		Mode mode = Mode::mainScreen;
		graphics::GLController& glController;
		serializable::ConfigManager& configManager;

		// vein
		vein::Node* rootNode;
		bool selectedLeft = true;
		bool firstRender = true;
		vein::Node* selectedNode = rootNode;

		// blood cells
		std::vector<bloodEditor*> editors;
		bloodEditor* selectedEditor = nullptr;

		void finalDraw();
		void createComponent();

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