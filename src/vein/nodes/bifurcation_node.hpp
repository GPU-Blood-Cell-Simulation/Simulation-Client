#pragma once

#include "node.hpp"
#include "../vein_generator.hpp"

namespace vein
{
	class BifurcationNode : public Node
	{
	public:
		BifurcationNode(Node* parent, float radiusLeft, float radiusRight,
			float leftYaw, float rightYaw, bool isLeft = true);
		BifurcationNode(Node* parent, const json& j, bool isLeft = true);

		BifurcationNode() = default;
		BifurcationNode(const BifurcationNode&) = delete;
		BifurcationNode(BifurcationNode&&) = default;
		BifurcationNode& operator=(const BifurcationNode&) = delete;
		BifurcationNode& operator=(BifurcationNode&&) = default;

		inline static const std::string type = "bifurcation";

		virtual void renderGUI(gui::GUIController& guiController) override;
		virtual void addToMesh(TempMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart,
			bool parentIsBifurcation) const override;
		virtual json generateJson() const override;

	protected:
		virtual std::string getFullName() const override;

	private:
		float radiusLeft, radiusRight, leftYaw, rightYaw;
	};
}