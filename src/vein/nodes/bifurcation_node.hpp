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
		BifurcationNode(Node* parent, const json& j, bool isLeft = true);

		BifurcationNode() = default;
		BifurcationNode(const BifurcationNode&) = delete;
		BifurcationNode(BifurcationNode&&) = default;
		BifurcationNode& operator=(const BifurcationNode&) = delete;
		BifurcationNode& operator=(BifurcationNode&&) = default;

		inline static const std::string type = "bifurcation";

		virtual void renderGUI(gui::GUIController& guiController, float width) override;
		virtual void addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart,
			bool parentIsBifurcation) const override;
		virtual json generateJson() const override;

	protected:
		virtual std::string getFullName() const override;

		virtual float leftChildButtonOffset() const override;
		virtual float rightChildButtonOffset() const override;
		inline virtual int getChildLevel() const override
		{
			return level + 1;
		}


	private:
		float radiusLeft, radiusRight, leftRoll, rightRoll, leftPitch, rightPitch;
	};
}