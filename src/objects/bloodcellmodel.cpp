#include "bloodcellmodel.hpp"
#include <string>
#include <format>
#include <fstream>
#include <algorithm>


void bloodcell::bloodCellModel::createHeaderFromData(int decimalPrecision)
{
	std::ifstream template_definition_header("SimulationConfigData\\template_bloodcells_definition.hpp");
	std::ofstream definition_header("Config\\blood_cells_definition.hpp");
	definition_header << template_definition_header.rdbuf();

	std::ifstream template_bloodcell_preset("SimulationConfigData\\template_blood_cell_presets.hpp");
	std::ofstream bloodcell_preset("Config\\blood_cell_presets.hpp");
	bloodcell_preset << template_bloodcell_preset.rdbuf();


	for (auto definition = predefinedModels.cbegin(); definition != predefinedModels.cend(); ++definition)
	{
		if (definition->quantity > 0)
		{
			definition_header << std::format("\r\n\tBloodCellDef<{}, {}, {},\n", definition->quantity, definition->vertices.size(), definition->indices.size());
			definition_header << std::format("\t\tpreset::{}_Springs,\n", definition->name);
			definition_header << std::format("\t\tpreset::{}_Vertices,\n", definition->name);
			definition_header << std::format("\t\tpreset::{}_Indices,\n", definition->name);
			definition_header << std::format("\t\tpreset::{}_Normals>{}\n", definition->name, (definition == std::prev(predefinedModels.end()) ? "" : ","));

			bloodcell_preset << std::format("\n\nusing {}_Springs = mp_list<\n", definition->name);

			int precision = decimalPrecision;
			for (auto spring = definition->springs.cbegin(); spring != definition->springs.cend(); ++spring)
			{
				glm::vec3 left = definition->vertices[spring->first], right = definition->vertices[spring->second];
				float length = sqrt(pow(left.x - right.x, 2) + pow(left.y - right.y, 2) + pow(left.z - right.z, 2));
				bloodcell_preset << std::format("\tSpring<{}, {}, {}, {}>{}\n", spring->first, spring->second,
					(int)(pow(10, precision) * length), precision, (spring == std::prev(definition->springs.end()) ? "" : ","));
			}

			bloodcell_preset << std::format(">;\n\nusing {}_Vertices = mp_list<\n", definition->name);
			for (auto vertex = definition->vertices.cbegin(); vertex != definition->vertices.cend(); ++vertex)
			{
				bloodcell_preset << std::format("\tmpFloat3<{}, {}, {}, {}>{}\n", (int)(pow(10, precision) * vertex->x),
					(int)(pow(10, precision) * vertex->y), (int)(pow(10, precision) * vertex->z), precision, (vertex == std::prev(definition->vertices.end()) ? "" : ","));
			}

			bloodcell_preset << std::format(">;\n\nusing {}_Indices = mp_list<\n", definition->name);

			for (auto indice = definition->indices.cbegin(); indice != definition->indices.cend(); indice += 3)
			{
				bloodcell_preset << std::format("\tmp_int<{}>, mp_int<{}>, mp_int<{}>{}\n", *indice,
					*(indice + 1), *(indice + 2), (indice + 2 == std::prev(definition->indices.cend()) ? "" : ","));
			}

			bloodcell_preset << std::format(">;\n\nusing {}_Normals = mp_list<\n", definition->name);

			for (auto normal = definition->normals.cbegin(); normal != definition->normals.cend(); ++normal)
			{
				bloodcell_preset << std::format("\tmpFloat3<{}, {}, {}, {}>{}\n", (int)(pow(10, precision) * normal->x),
					(int)(pow(10, precision) * normal->y), (int)(pow(10, precision) * normal->z), precision, (normal == std::prev(definition->normals.cend()) ? "" : ","));
			}

			bloodcell_preset << ">;\n";
		}
	}
	definition_header << "	> ;\n}";
	bloodcell_preset << "\n}";
}