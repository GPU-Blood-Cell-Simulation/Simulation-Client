#pragma once

#include "../../graphics/shader.hpp"
#include "../../serializable/util/nameof.hpp"
#include "../vein_mesh.hpp"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
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

	/// <summary>
	/// A base abstract class representing a single node in the vein - equivalent to a single segment.
	/// Various types of nodes are defined.
	/// </summary>
	class Node
	{
	public:
		virtual ~Node();

		/// <summary>
		/// Render the whole hierarchy of nodes in the GUI window as buttons. Traverses the tree using BFS.
		/// </summary>
		/// <param name="guiController">The GUIController instance</param>
		/// <param name="root">Root node to begin with</param>
		static void renderAll(gui::GUIController& guiController, Node* root);

		void markChildrenToBeDeleted(bool leftChild = true);
		void deleteMarkedChildren();

		void draw(Shader* shader) const;
		virtual void renderGUI(gui::GUIController& guiController, float width) = 0;
		virtual void addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart, 
			bool parentIsBifurcation = false) const = 0;
		virtual json generateJson() const = 0;

		Node* parent;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;

		glm::quat leftQuat;
		glm::quat rightQuat;

		glm::vec3 leftEndCenter;
		glm::vec3 rightEndCenter;
		float leftBranchRadius = 0;
		float rightBranchRadius = 0;

	private:
		inline static unsigned int objectCount = 0;
		bool leftToBeDeleted = false;
		bool rightToBeDeleted = false;

	protected:
		/// <summary>
		/// The basic contructor
		/// </summary>
		/// <param name="parent">Parent node in the vein tree</param>
		/// <param name="mesh">The generated mesh that will be assiociated with this node</param>
		/// <param name="leftBranchRadius">Radius of the left ending</param>
		/// <param name="rightBranchRadius">Radius of the right ending (if present)</param>
		/// <param name="isLeft">Whether this node is its parent's left child</param>
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
		void setupModelMatrix(const glm::vec3& translation, float rollAngle, float pitchAngle);

		virtual float leftChildButtonOffset() const = 0;
		virtual float rightChildButtonOffset() const = 0;
		virtual int getChildLevel() const = 0;

		VeinMesh mesh;

		const bool isLeft = true;
		unsigned int id = 0;
		int level = 1;
		static constexpr float buttonHeight = 40.0f;
		static constexpr float buttonWidth = 80.0f;
    
		glm::mat4 model{1.0f};
	};
}