#include "bifurcation_node.hpp"

#include "../../defines.hpp"

namespace vein
{
	void BifurcationNode::addToMesh(SerializableMesh& finalMesh, unsigned int parentLeftBranchLastRowStart, unsigned int parentRightBranchLastRowStart,
		bool parentIsBifurcation) const
	{
		unsigned int positionsInitialSize = finalMesh.positions.size();
		unsigned int previousMeshLastRowStart = isLeft ? parentLeftBranchLastRowStart : parentRightBranchLastRowStart;

		//// Copy positions
		// 3 * <segment> - <first and last row of first segment> - <half of second segment>
		finalMesh.positions.reserve(positionsInitialSize + 3 * bif::vLayers * bif::hLayers - 2 * bif::hLayers - bif::hLayers / 2);

		// First segment except for its first and last row
		std::transform(mesh.positions.cbegin() + bif::hLayers, mesh.positions.begin() + (bif::vLayers - 1) * bif::hLayers,
			std::back_inserter(finalMesh.positions), [&](auto&& position)
			{
				return model * glm::vec4(position, 1.0f);
			});
		unsigned int leftBranchFirstRowStart = finalMesh.positions.size();

		// Second (left) segment except for the left half of its first row
		std::transform(mesh.positions.cbegin() + bif::vLayers * bif::hLayers,
			mesh.positions.cbegin() + bif::vLayers * bif::hLayers + bif::hLayers / 4,
			std::back_inserter(finalMesh.positions), [&](auto&& position)
			{
				return model * glm::vec4(position, 1.0f);
			});
		// Skip left half
		std::transform(mesh.positions.cbegin() + bif::vLayers * bif::hLayers + 3 * bif::hLayers / 4,
			mesh.positions.cbegin() + 2 * bif::vLayers * bif::hLayers,
			std::back_inserter(finalMesh.positions), [&](auto&& position)
			{
				return model * glm::vec4(position, 1.0f);
			});
		unsigned int rightBranchFirstRowStart = finalMesh.positions.size();

		//// Third (right) segment
		std::transform(mesh.positions.cbegin() + 2 * bif::vLayers * bif::hLayers,
			mesh.positions.cend(),
			std::back_inserter(finalMesh.positions), [&](auto&& position)
			{
				return model * glm::vec4(position, 1.0f);
			});

		//// Transform indices
		// 3 * <segment> - <only first row of first segment> - <half of second segment>
		finalMesh.indices.reserve(finalMesh.indices.size() + 18 * (bif::vLayers - 1) * bif::hLayers - 6 * bif::hLayers);

		// Add first segment except for its first and last row
		unsigned int count = 0;
		std::transform(mesh.indices.cbegin() + 6 * bif::hLayers, mesh.indices.cbegin() + 6 * (bif::vLayers - 2) * bif::hLayers, std::back_inserter(finalMesh.indices), [&](auto&& index)
			{
				count++;
				return index + positionsInitialSize - bif::hLayers; // account for the removed first row
			});

		// Swap the last row of indices to glue the two meshes together
		unsigned int offsetFromPreviousMesh = (bif::vLayers - 3) * bif::hLayers; // because we are connecting end->end, not end->start
		if (parentIsBifurcation)
		{
			unsigned int modifiedOffset = offsetFromPreviousMesh + bif::hLayers / 2;
			for (int j = 0; j < bif::hLayers / 2; j++)
			{
				int nextj = j + 1;
				finalMesh.indices.push_back(positionsInitialSize + modifiedOffset - j);
				finalMesh.indices.push_back(previousMeshLastRowStart + j);
				finalMesh.indices.push_back(previousMeshLastRowStart + nextj);
				finalMesh.indices.push_back(positionsInitialSize + modifiedOffset - j);
				finalMesh.indices.push_back(previousMeshLastRowStart + nextj);
				finalMesh.indices.push_back(positionsInitialSize + modifiedOffset - nextj);
			}

			finalMesh.indices.push_back(positionsInitialSize + offsetFromPreviousMesh);
			finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers / 2);
			finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers / 2 + 1);
			finalMesh.indices.push_back(positionsInitialSize + offsetFromPreviousMesh);
			finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers / 2 + 1);
			finalMesh.indices.push_back(positionsInitialSize + offsetFromPreviousMesh + bif::hLayers - 1);

			modifiedOffset = offsetFromPreviousMesh + bif::hLayers;
			for (int j = 1; j < bif::hLayers / 2 - 1; j++)
			{
				int nextj = j + 1;
				finalMesh.indices.push_back(positionsInitialSize + modifiedOffset - j);
				finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers / 2 + j);
				finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers / 2 + nextj);
				finalMesh.indices.push_back(positionsInitialSize + modifiedOffset - j);
				finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers / 2 + nextj);
				finalMesh.indices.push_back(positionsInitialSize + modifiedOffset - nextj);
			}

			finalMesh.indices.push_back(positionsInitialSize + offsetFromPreviousMesh + bif::hLayers / 2 + 1);
			finalMesh.indices.push_back(previousMeshLastRowStart + bif::hLayers - 1);
			finalMesh.indices.push_back(previousMeshLastRowStart);
			finalMesh.indices.push_back(positionsInitialSize + offsetFromPreviousMesh + bif::hLayers / 2 + 1);
			finalMesh.indices.push_back(previousMeshLastRowStart);
			finalMesh.indices.push_back(positionsInitialSize + offsetFromPreviousMesh + bif::hLayers / 2);
		}
		else
		{
			for (int j = 0; j < bif::hLayers; j++)
			{
				int nextj = (j + 1) % bif::hLayers;
				finalMesh.indices.push_back(positionsInitialSize + offsetFromPreviousMesh + j);
				finalMesh.indices.push_back(previousMeshLastRowStart + j);
				finalMesh.indices.push_back(previousMeshLastRowStart + nextj);
				finalMesh.indices.push_back(positionsInitialSize + offsetFromPreviousMesh + j);
				finalMesh.indices.push_back(previousMeshLastRowStart + nextj);
				finalMesh.indices.push_back(positionsInitialSize + offsetFromPreviousMesh + nextj);
			}
		}
		

		// Glue the left part of the first segment's first row the the left branch segment's right side

		for (int j = 1; j < bif::hLayers / 4; j++)
		{
			int nextj = j + 1;
			
			
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 4 + nextj);
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 4 + j);
			finalMesh.indices.push_back(leftBranchFirstRowStart + bif::hLayers / 4 - j);
			finalMesh.indices.push_back(leftBranchFirstRowStart + bif::hLayers / 4 - nextj);
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 4 + nextj);
			finalMesh.indices.push_back(leftBranchFirstRowStart + bif::hLayers / 4 - j);
		}

		finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 2 + 1);
		finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 2);
		finalMesh.indices.push_back(leftBranchFirstRowStart);	
		finalMesh.indices.push_back(leftBranchFirstRowStart + bif::hLayers / 2 - 1);
		finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 2 + 1);
		finalMesh.indices.push_back(leftBranchFirstRowStart);

		for (int j = 1; j < bif::hLayers / 4; j++)
		{
			int nextj = j + 1;
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 2 + nextj);
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 2 + j);
			finalMesh.indices.push_back(leftBranchFirstRowStart + bif::hLayers / 2 - j);
			finalMesh.indices.push_back(leftBranchFirstRowStart + bif::hLayers / 2 - nextj);
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 2 + nextj);
			finalMesh.indices.push_back(leftBranchFirstRowStart + bif::hLayers / 2 - j);
		}

		// Glue the right part of the first segment's last row the the right branch segment's left side
		for (int j = 0; j < bif::hLayers / 4; j++)
		{
			int nextj = j + 1;
			finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 4 + nextj);
			finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 4 + j);
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 4 - j);
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 4 - nextj);
			finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 4 + nextj);		
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 4 - j);
		}

		finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 2 + 1);
		finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 2);
		finalMesh.indices.push_back(positionsInitialSize);
		finalMesh.indices.push_back(positionsInitialSize + bif::hLayers - 1);
		finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 2 + 1);
		finalMesh.indices.push_back(positionsInitialSize);

		for (int j = 1; j < bif::hLayers / 4; j++)
		{
			int nextj = j + 1;
			finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 2 + nextj);
			finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 2 + j);
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers - j);
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers - nextj);
			finalMesh.indices.push_back(rightBranchFirstRowStart +  bif::hLayers / 2 + nextj);
			finalMesh.indices.push_back(positionsInitialSize + bif::hLayers - j);
		}

		// Add second segment except for the left half of its first row
		std::transform(mesh.indices.cbegin() + 6 * (bif::vLayers - 1) * bif::hLayers, mesh.indices.cbegin() + 6 * ((bif::vLayers - 1) * bif::hLayers + bif::hLayers / 4 - 1),
			std::back_inserter(finalMesh.indices), [&](auto&& index)
			{
				static unsigned int i = 0;
				auto isNextRow = i++ % 6;
				return (isNextRow == 0 || isNextRow == 3 || isNextRow == 5) ?
					index + leftBranchFirstRowStart - bif::vLayers * bif::hLayers - bif::hLayers / 2 :
					index + leftBranchFirstRowStart - bif::vLayers * bif::hLayers; // i + shift - (shift index to 0)
			});

		// special case for last vertex in the first quarter of the left branch's first row
		finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 4);		
		finalMesh.indices.push_back(leftBranchFirstRowStart + 3 * bif::hLayers / 4 - 1);
		finalMesh.indices.push_back(leftBranchFirstRowStart + bif::hLayers / 4 - 1);
		finalMesh.indices.push_back(leftBranchFirstRowStart + 3 * bif::hLayers / 4);
		finalMesh.indices.push_back(leftBranchFirstRowStart + 3 * bif::hLayers / 4 - 1);
		finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 4);

		std::transform(mesh.indices.cbegin() + 6 * ((bif::vLayers - 1) * bif::hLayers + 3 * bif::hLayers / 4), mesh.indices.cbegin() + 6 * (bif::vLayers * bif::hLayers - 1),
			std::back_inserter(finalMesh.indices), [&](auto&& index)
			{
				return index + leftBranchFirstRowStart - bif::vLayers * bif::hLayers - bif::hLayers / 2;
			});

		// special case for last in row
		finalMesh.indices.push_back(leftBranchFirstRowStart + 3 * bif::hLayers / 2 - 1);
		finalMesh.indices.push_back(leftBranchFirstRowStart + bif::hLayers / 2 - 1);
		finalMesh.indices.push_back(leftBranchFirstRowStart);
		finalMesh.indices.push_back(leftBranchFirstRowStart + 3 * bif::hLayers / 2 - 1);
		finalMesh.indices.push_back(leftBranchFirstRowStart);
		finalMesh.indices.push_back(leftBranchFirstRowStart + bif::hLayers / 2);
		
		std::transform(mesh.indices.cbegin() + 6 * bif::vLayers * bif::hLayers, mesh.indices.cbegin() + 6 * 2 * (bif::vLayers - 1) * bif::hLayers,
			std::back_inserter(finalMesh.indices), [&](auto&& index)
			{
				return index + leftBranchFirstRowStart - bif::vLayers * bif::hLayers - bif::hLayers / 2;
			});

		// Glue the left half of the left segment to the right half of the right segment
		unsigned leftBranchGlueStart = leftBranchFirstRowStart + bif::hLayers / 2;
		for (int j = 0; j < bif::hLayers / 4; j++)
		{
			int nextj = j + 1;
			finalMesh.indices.push_back(leftBranchGlueStart + bif::hLayers / 4 + nextj);			
			finalMesh.indices.push_back(leftBranchGlueStart + bif::hLayers / 4 + j);
			finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 4 - j);
			finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 4 - nextj);
			finalMesh.indices.push_back(leftBranchGlueStart + bif::hLayers / 4 + nextj);
			finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 4 - j);
		}

		finalMesh.indices.push_back(leftBranchGlueStart + bif::hLayers / 2 + 1);
		finalMesh.indices.push_back(leftBranchGlueStart + bif::hLayers / 2);
		finalMesh.indices.push_back(rightBranchFirstRowStart);
		finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers - 1);
		finalMesh.indices.push_back(leftBranchGlueStart + bif::hLayers / 2 + 1);
		finalMesh.indices.push_back(rightBranchFirstRowStart);

		for (int j = 1; j < bif::hLayers / 4 - 1; j++)
		{
			int nextj = j + 1;
			finalMesh.indices.push_back(leftBranchGlueStart + bif::hLayers / 2 + nextj);
			finalMesh.indices.push_back(leftBranchGlueStart + bif::hLayers / 2 + j);
			finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers - j);
			finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers - nextj);
			finalMesh.indices.push_back(leftBranchGlueStart + bif::hLayers / 2 + nextj);
			finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers - j);
		}

		// special case - glueing front
		finalMesh.indices.push_back(leftBranchFirstRowStart + bif::hLayers / 4 - 1);
		finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 4);
		finalMesh.indices.push_back(rightBranchFirstRowStart + bif::hLayers / 4);
		finalMesh.indices.push_back(leftBranchFirstRowStart + bif::hLayers / 4 - 1);
		finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 4 + 1);
		finalMesh.indices.push_back(positionsInitialSize + bif::hLayers / 4);

		// special case - glueing back
		finalMesh.indices.push_back(rightBranchFirstRowStart + 3 * bif::hLayers / 4);
		finalMesh.indices.push_back(leftBranchFirstRowStart + 5 * bif::hLayers / 4);
		finalMesh.indices.push_back(leftBranchFirstRowStart + 5 * bif::hLayers / 4 - 1);
		finalMesh.indices.push_back(rightBranchFirstRowStart + 3 * bif::hLayers / 4 + 1);
		finalMesh.indices.push_back(rightBranchFirstRowStart + 3 * bif::hLayers / 4);
		finalMesh.indices.push_back(leftBranchFirstRowStart + 5 * bif::hLayers / 4 - 1);

		// Add third segment
		std::transform(mesh.indices.cbegin() + 2 * 6 * (bif::vLayers - 1) * bif::hLayers, mesh.indices.end(),
			std::back_inserter(finalMesh.indices), [&](auto&& index)
			{
				return index + rightBranchFirstRowStart - 2 * bif::vLayers * bif::hLayers;
			});

		// Recurse
		unsigned int thisSegmentLeftBranchLastRowStart = positionsInitialSize + 2 * bif::vLayers * bif::hLayers - 3 * bif::hLayers - bif::hLayers / 2;
		unsigned int thisSegmentRightBranchLastRowStart = positionsInitialSize + 3 * bif::vLayers * bif::hLayers - 3 * bif::hLayers - bif::hLayers / 2;
		if (left)
		{
			left->addToMesh(finalMesh, thisSegmentLeftBranchLastRowStart, thisSegmentRightBranchLastRowStart, true);
		}
		else
		{
			finalMesh.addEnding(leftEndCenter, leftBranchRadius);
		}

		if (right)
		{
			
			right->addToMesh(finalMesh, thisSegmentLeftBranchLastRowStart, thisSegmentRightBranchLastRowStart, true);
		}
		else
		{
			finalMesh.addEnding(rightEndCenter, rightBranchRadius);
		}
	}
}