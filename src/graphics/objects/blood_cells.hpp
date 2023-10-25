#pragma once

#include "blood_cell_def.hpp"

#include <nlohmann/json.hpp>
#include <vector>

namespace graphics
{
	using json = nlohmann::json;

	class BloodCells
	{
        std::vector<BloodCellDef> definitions;
	};

    void to_json(json& j, const BloodCells& bloodCells)
    {
        j = json{ {"name", p.name}, {"address", p.address}, {"age", p.age} };
    }

    void from_json(const json& j, BloodCells& p)
    {
        j.at("name").get_to(p.name);
        j.at("address").get_to(p.address);
        j.at("age").get_to(p.age);
    }
}

