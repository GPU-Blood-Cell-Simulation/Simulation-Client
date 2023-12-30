#pragma once

#include "../../graphics/shader.hpp"
#include "../../serializable/util/nameof.hpp"
#include "../vein_mesh.hpp"

#include <memory>
#include <nlohmann/json.hpp>
#include <tuple>

namespace gui
{
	class GUIController;
}

namespace vein
{
	using json = nlohmann::json;

	class Node
	{
	public:
		virtual ~Node();

		static void renderAll(gui::GUIController& guiController, Node* root);

		void markChildrenToBeDeleted(bool leftChild = true);
		void deleteMarkedChildren();

		void draw(Shader* shader) const;
		virtual void renderGUI(gui::GUIController& guiController) = 0;
		virtual void addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart, 
			bool parentIsBifurcation = false) const = 0;
		virtual json generateJson() const = 0;

		Node* parent;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;

		float leftBranchAngle = 0;
		float rightBranchAngle = 0;
		glm::vec3 leftEndCenter;
		glm::vec3 rightEndCenter;
		float leftBranchRadius = 0;
		float rightBranchRadius = 0;

	private:
		inline static unsigned int objectCount = 0;
		bool leftToBeDeleted = false;
		bool rightToBeDeleted = false;

	protected:
		Node(Node* parent, VeinMesh&& mesh, float leftBranchRadius, float rightBranchRadius, bool isLeft = true);

		// constructors needed for json serialization
		Node() = default;
		Node(const Node&) = delete;
		Node(Node&&) = default;
		Node& operator=(const Node&) = delete;
		Node& operator=(Node&&) = default;

		virtual std::string getFullName() const = 0;
		std::string getPopupName() const;
		std::tuple<json, json> generateLeftAndRightJson() const;
		void fillLeftAndRightFromJson(const json& j);

		VeinMesh mesh;

		const bool isLeft = true;
		unsigned int id = 0;
    
		glm::mat4 model;
	};
}