#pragma once

#include "blood_cell_type.hpp"
#include "cpp_serializable.hpp"

#include <algorithm>
#include <nlohmann/json.hpp>
#include <vector>

namespace serializable
{
	using json = nlohmann::json;

	struct BloodCellsDefinition : public ICppSerializable
	{
        std::vector<BloodCellType> bloodCellTypes;

        int getBloodCellCount() const
        {
            return std::accumulate(bloodCellTypes.begin(), bloodCellTypes.end(), 0, [](int sum, BloodCellType type) { return sum + type.quantity; });
        }

        int getParticleCount() const
        {
            return std::accumulate(bloodCellTypes.begin(), bloodCellTypes.end(), 0, [](int sum, BloodCellType type) { return sum + type.quantity * type.modelSize; });
        }

		virtual void serializeToCpp() const override;
	};

    inline void to_json(json& j, const BloodCellsDefinition& o)
    {
        j = json{ {"models", o.bloodCellTypes} };
    }

    inline void from_json(const json& j, BloodCellsDefinition& o)
    {
		j.at("models").get_to(o.bloodCellTypes);
    }
}

