#pragma once

#include "../graphics/glcontroller.hpp"
#include "../serializable/config_manager.hpp"

#include <imgui/imgui/imgui.h>

namespace gui
{
	/// <summary>
	/// A class responsible for rendering the UI and processing user input
	/// </summary>
	class GUIController
	{
	public:
		GUIController(GLFWwindow* window, graphics::GLController& glController, serializable::ConfigManager& configManager);
		void renderUI();
	private:
		ImGuiIO& io;

		graphics::GLController& glController;
		serializable::ConfigManager& configManager;
		void finalDraw();
	};
}