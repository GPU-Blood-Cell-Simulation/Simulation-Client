#pragma once

#include "node.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	class BifurcationNode : public Node
	{
	public:
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