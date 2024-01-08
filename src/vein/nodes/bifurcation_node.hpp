#pragma once

#include "node.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	/// <summary>
	/// A node type that has one opening but two ends. Therefore two branches can be attached to it.
	/// Both of its endings can be altered separately;
	/// </summary>
	class BifurcationNode : public Node
	{
	public:
		/// <summary>
		/// The basic constructor
		/// </summary>
		/// <param name="parent">Parent node in the vein tree</param>
		/// <param name="radiusLeft">Radius of the left ending</param>
		/// <param name="radiusRight">Radius of the right ending</param>
		/// <param name="leftRoll">Left branch rotation with respect to the roll angle</param>
		/// <param name="rightRoll">Right branch rotation with respect to the roll angle</param>
		/// <param name="leftPitch">Left branch rotation with respect to the pitch angle</param>
		/// <param name="rightPitch">Right branch rotation with respect to the pitch angle</param>
		/// <param name="isLeft">Whether this node is its parent's left child</param>
		BifurcationNode(Node* parent, float radiusLeft, float radiusRight,
			float leftRoll, float rightRoll, float leftPitch, float rightPitch, bool isLeft = true);

		/// <summary>
		/// Constructor from json
		/// </summary>
		/// <param name="parent">The parent node pointer</param>
		/// <param name="j">A json describing this node and its children (if present)</param>
		/// <param name="isLeft">Whether this node is its parent's left child</param>
		BifurcationNode(Node* parent, const json& j, bool isLeft = true);

		BifurcationNode() = default;
		BifurcationNode(const BifurcationNode&) = delete;
		BifurcationNode(BifurcationNode&&) = default;
		BifurcationNode& operator=(const BifurcationNode&) = delete;
		BifurcationNode& operator=(BifurcationNode&&) = default;

		inline static const std::string type = "bifurcation";

		/// <summary>
		/// Renders a button in a tree-like hierarchy in the ImGui window
		/// </summary>
		/// <param name="guiController">The GUIController instance</param>
		/// <param name="width">the window width at which the center of the button should be rendered</param>
		virtual void renderGUI(gui::GUIController& guiController, float width) override;

		/// <summary>
		/// Adds this node's mesh to the final mesh and glues them together. Additionally glues the internal segments
		/// of the bifurcation mesh
		/// </summary>
		/// <param name="finalMesh">The final mesh that this node will append to</param>
		/// <param name="parentLeftBranchLastRowStart">The starting index of the parent's left branch's last row</param>
		/// <param name="parentRightBranchLastRowStart">The starting index of the parent's right branch's last row</param>
		/// <param name="parentIsBifurcation">Whether the parent is a bifurcation (has two endings)</param>
		virtual void addToMesh(SerializableMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart,
			bool parentIsBifurcation) const override;

		/// <summary>
		/// Generate a json sub-object containing the information needed to reconstruct this node and its children (if present) recursively
		/// </summary>
		/// <returns>A json object</returns>
		virtual json generateJson() const override;

	protected:
		virtual std::string getFullName() const override;

		virtual float leftChildButtonOffset() const override;
		virtual float rightChildButtonOffset() const override;

		/// <summary>
		/// Increases the children's level by one
		/// </summary>
		/// <returns>Children's level in the tree hierarchy</returns>
		inline virtual int getChildLevel() const override
		{
			return level + 1;
		}

	private:
		float radiusLeft, radiusRight, leftRoll, rightRoll, leftPitch, rightPitch;
	};
}