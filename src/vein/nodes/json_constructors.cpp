#include "root_node.hpp"
#include "cylinder_node.hpp"
#include "bifurcation_node.hpp"

namespace vein
{
	void Node::fillLeftAndRightFromJson(const json& j)
	{
		if (!j.at(nameof(left)).is_null())
		{
			auto& leftJson = j.at(nameof(left));
			if (leftJson.at(nameof(type)) == CylinderNode::type)
			{
				left = std::make_unique<CylinderNode>(this, leftJson, true);
			}
			else if (leftJson.at(nameof(type)) == BifurcationNode::type)
			{
				left = std::make_unique<BifurcationNode>(this, leftJson, true);
			}
		}

		if (!j.at(nameof(right)).is_null())
		{
			auto& rightJson = j.at(nameof(right));
			if (rightJson.at(nameof(type)) == CylinderNode::type)
			{
				right = std::make_unique<CylinderNode>(this, rightJson, false);
			}
			else if (rightJson.at(nameof(type)) == BifurcationNode::type)
			{
				right = std::make_unique<BifurcationNode>(this, rightJson, false);
			}
		}
	}

	RootNode::RootNode(const json& j) : RootNode()
	{
		fillLeftAndRightFromJson(j);
	}

	CylinderNode::CylinderNode(Node* parent, const json& j, bool isLeft) : CylinderNode(parent,
		j.at(nameof(radius)).template get<float>(),
		j.at(nameof(vLayers)).template get<int>(),
		j.at(nameof(skew)).template get<float>(),
		isLeft)
	{
		fillLeftAndRightFromJson(j);
	}

	BifurcationNode::BifurcationNode(Node* parent, const json& j, bool isLeft) : BifurcationNode(parent,
		j.at(nameof(radiusLeft)).template get<float>(),
		j.at(nameof(radiusRight)).template get<float>(),
		j.at(nameof(leftRotation)).template get<float>(),
		j.at(nameof(rightRotation)).template get<float>(),
		isLeft)
	{
		fillLeftAndRightFromJson(j);
	}
}