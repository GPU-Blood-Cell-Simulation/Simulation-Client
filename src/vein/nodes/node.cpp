#include "node.hpp"
#include "../../gui/gui_controller.hpp"

#include <queue>

#include <iostream>

namespace vein
{
	Node::Node(Node* parent, VeinMesh&& mesh, float leftBranchRadius, float rightBranchRadius, bool isLeft) :
		parent(parent), mesh(mesh), leftBranchRadius(leftBranchRadius), rightBranchRadius(rightBranchRadius), isLeft(isLeft),
		id(objectCount++) {}

	Node::~Node()
	{
		objectCount--;
	}

	void Node::renderAll(gui::GUIController& guiController, Node* root)
	{
		std::queue<Node*> q;
		q.push(root);

		while (q.size() > 0)
		{
			int levelNodes = q.size();
			while (levelNodes > 0)
			{
				Node* p = q.front();
				q.pop();

				p->renderGUI(guiController);
				ImGui::SameLine();

				if (p->left) q.push((p->left).get());
				if (p->right) q.push((p->right).get());

				levelNodes--;
			}
			ImGui::NewLine();
		}
	}

	// Defer deleting the children until the next frame because the children need to finish rendering their gui components
	void Node::markChildrenToBeDeleted(bool leftChild)
	{
		if (leftChild)
		{
			leftToBeDeleted = true;
		}
		else
		{
			rightToBeDeleted = true;
		}
	}

	void Node::deleteMarkedChildren()
	{
		if (leftToBeDeleted)
		{
			left.reset();
			leftToBeDeleted = false;
		}
		if (rightToBeDeleted)
		{
			right.reset();
			rightToBeDeleted = false;
		}

		if (left)
		{
			left->deleteMarkedChildren();
		}
		if (right)
		{
			right->deleteMarkedChildren();
		}
	}

	void Node::draw(Shader* shader) const
	{
		shader->setMatrix("model", model);
		mesh.draw(shader);

		if (left)
		{
			left->draw(shader);
		}
		if (right)
		{
			right->draw(shader);
		}
	}

	std::string Node::getPopupName() const
	{
		return "popup{}" + std::to_string(id);
	}

	std::tuple<json, json> Node::generateLeftAndRightJson() const
	{
		json leftJson = left ? json{ nameof(left), left->generateJson()} : json{ nameof(left), nullptr};
		json rightJson = right ? json{ nameof(right), right->generateJson() } : json{ nameof(right), nullptr };
		return std::tuple(std::move(leftJson), std::move(rightJson));
	}

	void Node::setupModelMatrix(const glm::vec3& translation, float rollAngle, float pitchAngle)
	{
		model = glm::translate(glm::mat4(1.0f), translation) *
			glm::rotate(glm::mat4(1.0f), pitchAngle, glm::vec3(1, 0, 0)) *
			glm::rotate(glm::mat4(1.0f), rollAngle, glm::vec3(0, 0, 1));
	}
}