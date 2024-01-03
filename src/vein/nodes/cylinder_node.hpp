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
		CylinderNode(Node* parent, const json& j, bool isLeft = true);

		CylinderNode() = default;
		CylinderNode(const CylinderNode&) = delete;
		CylinderNode(CylinderNode&&) = default;
		CylinderNode& operator=(const CylinderNode&) = delete;
		CylinderNode& operator=(CylinderNode&&) = default;

		inline static const std::string type = "cylinder";

		virtual void renderGUI(gui::GUIController& guiController, float width) override;
		virtual void addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchIndicesEnd, unsigned int parentRightBranchIndicesEnd,
			bool parentIsBifurcation) const override;
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