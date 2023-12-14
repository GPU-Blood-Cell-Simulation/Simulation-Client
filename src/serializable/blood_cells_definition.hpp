#pragma once

#include "blood_cell_type.hpp"
#include "../objects/bloodcellmodel.hpp"
#include <algorithm>
#include <nlohmann/json.hpp>
#include <vector>
#include <utility>

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

    /*inline void to_json(json& j, const BloodCellsDefinition& o)
    {
        j = json{ {"types", o.bloodCellTypes} };

    }*/

    inline void to_json(json& j)
    {
        j["decimalPrecision"] = 5;
        for (auto& definition : bloodcell::bloodCellModel::predefinedModels)
        {
            json cellType;
            cellType["name"] = definition.name;
            cellType["quantity"] = definition.quantity;
            for (auto& spring : definition.springs)
                cellType["springs"].push_back({ spring.first, spring.second });
            for (auto& vertex : definition.vertices)
                cellType["vertices"].push_back({ vertex.x, vertex.y, vertex.z });
            for (auto& index : definition.indices)
                cellType["indices"].push_back(index);
            for (auto& normal : definition.normals)
                cellType["normals"].push_back({ normal.x, normal.y, normal.z });

            // add model to list
            j["models"].push_back(cellType);
        }
    }

    inline void from_json(const json& j)
    {
        int decimalPrecision = j["decimalPrecision"];
        for (json definition : j["models"])
        {
            bloodcell::bloodCellModel_data data;
            data.name = definition["name"];
            data.quantity = definition["quantity"];
            for (json spring : definition["springs"])
            {
                data.springs.push_back(std::make_pair(std::stoi(spring[0].dump()), std::stoi(spring[1].dump())));
            }
            for (json vertex : definition["vertices"])
            {
                data.vertices.push_back(glm::vec3(std::stof(vertex[0].dump()),
                    std::stof(vertex[1].dump()), std::stof(vertex[2].dump())));
            }
            for (json index : definition["indices"])
            {
                data.indices.push_back(std::stoi(index.dump()));
            }
            for (json normal : definition["normals"])
            {
                data.normals.push_back(glm::vec3(std::stof(normal[0].dump()),
                    std::stof(normal[1].dump()), std::stof(normal[2].dump())));
            }
            bloodcell::bloodCellModel::predefinedModels[0] = data;
        }
    }

    /*inline void from_json(const json& j, BloodCellsDefinition& o)
    {
        j.at("types").get_to(o.bloodCellTypes);
    }*/
}

