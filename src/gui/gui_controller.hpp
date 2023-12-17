#pragma once

#include "../graphics/glcontroller.hpp"
#include "../serializable/config_manager.hpp"
#include "../vein/nodes/node.hpp"

#include <imgui/imgui/imgui.h>

namespace gui
{
	enum class Mode
	{
		mainScreen,
		generalEdit,
		bloodEdit,
		veinEdit,
		addVein,
		simulation
	};

	class GUIController
	{
	public:
		GUIController(GLFWwindow* window, graphics::GLController& glController, serializable::ConfigManager& configManager, vein::Node* rootNode);
		void renderUI();

		void setMode(Mode mode);
		void selectNode(vein::Node* node, bool selectedLeft = true);

	private:
		ImGuiIO& io;

		Mode mode = Mode::mainScreen;
		graphics::GLController& glController;
		serializable::ConfigManager& configManager;
		vein::Node* rootNode;

		bool selectedLeft = true;
		bool firstRender = true;
		vein::Node* selectedNode = rootNode;

		void finalDraw();
		void createComponent();

		// Components
		void renderMainScreen();
		void renderGeneralEditor();
		void renderBloodEditor();
		void renderVeinEditor();
		void renderAddVein();
		void renderSimulation();
	};
}