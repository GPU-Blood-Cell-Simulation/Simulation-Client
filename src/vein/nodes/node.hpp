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

		/// <summary>
		/// Draw the node's mesh in the OpenGL window
		/// </summary>
		/// <param name="shader">The shader used for this draw call</param>
		void draw(Shader* shader) const;

		/// <summary>
		/// Renders a button in a tree-like hierarchy in the ImGui window
		/// </summary>
		/// <param name="guiController">The GUIController instance</param>
		/// <param name="width">the window width at which the center of the button should be rendered</param>
		virtual void renderGUI(gui::GUIController& guiController, float width) = 0;

		/// <summary>
		/// Adds this node's mesh to the final mesh and glues them together
		/// </summary>
		/// <param name="finalMesh">The final mesh that this node will append to</param>
		/// <param name="parentLeftBranchLastRowStart">The starting index of the parent's left branch's last row</param>
		/// <param name="parentRightBranchLastRowStart">The starting index of the parent's right branch's last row</param>
		/// <param name="parentIsBifurcation">Whether the parent is a bifurcation (has two endings)</param>
		virtual void addToMesh(SerializableMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart, 
			bool parentIsBifurcation = false) const = 0;

		/// <summary>
		/// Generate a json sub-object containing the information needed to reconstruct this node and its children (if present) recursively
		/// </summary>
		/// <returns>A json object</returns>
		virtual json generateJson() const = 0;

		Node* parent;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;

		glm::quat leftQuat {glm::vec3(0, 0, 0)};
		glm::quat rightQuat {glm::vec3(0, 0, 0)};

		glm::vec3 leftEndCenter {0, 0, 0};
		glm::vec3 rightEndCenter {0, 0, 0};
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

		/// <summary>
		/// Returns the node's name in the form of its type and unique id
		/// </summary>
		/// <returns>The node's full name</returns>
		virtual std::string getFullName() const = 0;

		/// <summary>
		/// Returns the node's unique ImGui popup identifier
		/// </summary>
		/// <returns>The node's ImGui popup name</returns>
		std::string getPopupName() const;

		/// <summary>
		/// Recursively generates the json sub-objects from its left and right child (if present)
		/// </summary>
		/// <returns>Both its children's generated jsons as a tuple</returns>
		std::tuple<json, json> generateLeftAndRightJson() const;

		/// <summary>
		/// Based on the json provided, this node attaches two new nodes as children 
		/// </summary>
		/// <param name="j">A json describing this node</param>
		void fillLeftAndRightFromJson(const json& j);

		virtual float leftChildButtonOffset() const = 0;
		virtual float rightChildButtonOffset() const = 0;

		/// <summary>
		/// Calculates children's level in the node tree
		/// </summary>
		/// <returns>The level in tree hierarchy of this node's children</returns>
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