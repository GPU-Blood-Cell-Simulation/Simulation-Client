#pragma once

#include "../../graphics/shader.hpp"
#include "../vein_mesh.hpp"

#include <memory>

namespace gui
{
	class GUIController;
}

namespace vein
{
	class Node
	{
	public:
		static void renderAll(gui::GUIController& guiController, Node* root);

		void markChildrenToBeDeleted(bool leftChild = true);
		void deleteMarkedChildren();

		void draw(Shader* shader) const;
		virtual void renderGUI(gui::GUIController& guiController) = 0;
		virtual void addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart, 
			bool parentIsBifurcation = false) const = 0;

		Node* parent;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;

		float leftBranchAngle;
		float rightBranchAngle;
		glm::vec3 leftEndCenter;
		glm::vec3 rightEndCenter;

	private:
		inline static unsigned int objectCount = 0;
		bool leftToBeDeleted = false;
		bool rightToBeDeleted = false;

	protected:
		Node(Node* parent, VeinMesh&& mesh, bool isLeft);

		virtual const std::string getFullName() const = 0;

		VeinMesh mesh;

		const bool isLeft = true;

		const unsigned int id;
		const std::string popupName = "popup{}" + std::to_string(id);
    
		glm::mat4 model;
	};
}