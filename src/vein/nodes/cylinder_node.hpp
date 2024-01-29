#pragma once

#include "../../defines.hpp"
#include "node.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	/// <summary>
	/// A node type that represents a standard vein segment with one opening and one end. Can be bent into all directions.
	/// </summary>
	class CylinderNode : public Node
	{
	public:
		/// <summary>
		/// The basic contructor
		/// </summary>
		/// <param name="parent">Parent node in the vein tree</param>
		/// <param name="radius">Radius of the ending</param>
		/// <param name="vLayers">Vein length (vertical layers)</param>
		/// <param name="skewRoll">Vein skew with respect to the roll angle</param>
		/// <param name="skewPitch">Vein skew with respect to the pitch angle</param>
		/// <param name="isLeft">Whether this node is its parent's left child</param>
		CylinderNode(Node* parent, float radius, int vLayers, float skewRoll, float skewPitch, bool isLeft = true);

		/// <summary>
		/// Constructor from json
		/// </summary>
		/// <param name="parent">The parent node pointer</param>
		/// <param name="j">A json describing this node and its children (if present)</param>
		/// <param name="isLeft">Whether this node is its parent's left child</param>
		CylinderNode(Node* parent, const json& j, bool isLeft = true);

		CylinderNode() = default;
		CylinderNode(const CylinderNode&) = delete;
		CylinderNode(CylinderNode&&) = default;
		CylinderNode& operator=(const CylinderNode&) = delete;
		CylinderNode& operator=(CylinderNode&&) = default;

		inline static const std::string type = "cylinder";

		/// <summary>
		/// Renders a button in a tree-like hierarchy in the ImGui window
		/// </summary>
		/// <param name="guiController">The GUIController instance</param>
		/// <param name="width">the window width at which the center of the button should be rendered</param>
		virtual void renderGUI(gui::GUIController& guiController, float width) override;

		/// <summary>
		/// Adds this node's mesh to the final mesh and glues them together
		/// </summary>
		/// <param name="finalMesh">The final mesh that this node will append to</param>
		/// <param name="parentLeftBranchLastRowStart">The starting index of the parent's left branch's last row</param>
		/// <param name="parentRightBranchLastRowStart">The starting index of the parent's right branch's last row</param>
		/// <param name="parentIsBifurcation">Whether the parent is a bifurcation (has two endings)</param>
		virtual void addToMesh(SerializableMesh& finalMesh, unsigned int parentLeftBranchIndicesEnd, unsigned int parentRightBranchIndicesEnd,
			bool parentIsBifurcation) const override;

		/// <summary>
		/// Generate a json sub-object containing the information needed to reconstruct this node and its child (if present) recursively
		/// </summary>
		/// <returns>A json object</returns>
		virtual json generateJson() const override;

	protected:
		virtual std::string getFullName() const override;

		inline virtual float leftChildButtonOffset() const override
		{
			return 0;
		}
		inline virtual float rightChildButtonOffset() const override
		{
			return 0;
		}

		/// <summary>
		/// Returns own level (a cylinder node doesn't split)
		/// </summary>
		/// <returns>Children's level in the tree hierarchy</returns>
		inline virtual int getChildLevel() const override
		{
			return level;
		}

		float radius;
		int vLayers;
		float skewRoll;
		float skewPitch;
	};
}