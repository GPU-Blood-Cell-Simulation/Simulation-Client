#pragma once

#include "blood_cell_type.hpp"

#include <algorithm>
#include <nlohmann/json.hpp>
#include <vector>

namespace serializable
{
	using json = nlohmann::json;

	struct BloodCellsDefinition
	{
        std::vector<BloodCellType> bloodCellTypes{
            { 2, 3, 
                { {0, 1, 10}, {1, 2, 10 }, {2, 0, 10} } 
            } 
        };

        int getBloodCellCount() const
        {
            return std::accumulate(bloodCellTypes.begin(), bloodCellTypes.end(), 0, [](int sum, BloodCellType type) { return sum + type.count; });
        }

        int getParticleCount() const
        {
            return std::accumulate(bloodCellTypes.begin(), bloodCellTypes.end(), 0, [](int sum, BloodCellType type) { return sum + type.count * type.particlesInCell; });
        } 
	};

    inline void to_json(json& j, const BloodCellsDefinition& o)
    {
        j = json{ {"types", o.bloodCellTypes} };
    }

    inline void from_json(const json& j, BloodCellsDefinition& o)
    {
        j.at("types").get_to(o.bloodCellTypes);
    }
}

