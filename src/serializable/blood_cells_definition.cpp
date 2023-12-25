#include "blood_cells_definition.hpp"

#include "../defines.hpp"

#include <utility>
#include <fstream>


namespace serializable
{
    void BloodCellsDefinition::serializeToCpp() const
    {
		std::ifstream templateDefinitionHeader(bloodCellsDefinitionConfigDataPath);
		std::ofstream definitionHeader(bloodCellsDefinitionCppSerializationPath);
		definitionHeader << templateDefinitionHeader.rdbuf();

		std::ifstream template_bloodcell_preset(bloodCellPresetsConfigDataPath);
		std::ofstream bloodcell_preset(bloodCellPresetsCppSerializationPath);
		bloodcell_preset << template_bloodcell_preset.rdbuf();


		for (auto definition = bloodCellTypes.cbegin(); definition != bloodCellTypes.cend(); ++definition)
		{
			if (definition->quantity > 0)
			{
				definitionHeader << "\r\n\tBloodCellDef<" << definition->quantity << ", " << definition->vertices.size() << ", " << definition->indices.size() << ",\n";
				definitionHeader << "\t\tpreset::" << definition->name << "_Springs,\n";
				definitionHeader << "\t\tpreset::" << definition->name << "_Vertices,\n";
				definitionHeader << "\t\tpreset::" << definition->name << "_Indices,\n";
				definitionHeader << "\t\tpreset::" << definition->name << "_Normals>" << (definition == std::prev(bloodCellTypes.cend()) ? "" : ",") << "\n";

				bloodcell_preset << "\n\nusing " << definition->name << "_Springs = mp_list<\n";

				int precision = decimalPrecision;
				for (auto spring = definition->springs.cbegin(); spring != definition->springs.cend(); ++spring)
				{
					glm::vec3 left = definition->vertices[spring->from], right = definition->vertices[spring->to];
					float length = sqrt(pow(left.x - right.x, 2) + pow(left.y - right.y, 2) + pow(left.z - right.z, 2));
					bloodcell_preset << "\tSpring<" << spring->from << ", " << spring->to << ", " << static_cast<int>(pow(10, precision) * length)
						<< ", " << precision << ">" << (spring == std::prev(definition->springs.end()) ? "" : ",") << "\n";
				}

				bloodcell_preset << ">;\n\nusing " << definition->name << "_Vertices = mp_list<\n";
				for (auto vertex = definition->vertices.cbegin(); vertex != definition->vertices.cend(); ++vertex)
				{
					bloodcell_preset << "\tmpFloat3<" << static_cast<int>(pow(10, precision) * vertex->x) << ", "
						<< static_cast<int>(pow(10, precision) * vertex->y) << ", " << static_cast<int>(pow(10, precision) * vertex->z) << ", "
						<< precision << ">" << (vertex == std::prev(definition->vertices.end()) ? "" : ",") << "\n";
				}

				bloodcell_preset << ">;\n\nusing " << definition->name << "_Indices = mp_list<\n";

				for (auto index= definition->indices.cbegin(); index!= definition->indices.cend(); index+= 3)
				{
					bloodcell_preset << "\tmp_int<" << *index << ">, mp_int<" << *(index + 1) << ">, mp_int<" << *(index + 2) << ">"
						<< (index + 2 == std::prev(definition->indices.cend()) ? "" : ",") << "\n"; 
				}

				bloodcell_preset << ">;\n\nusing " << definition->name << "_Normals = mp_list<\n";

				for (auto normal = definition->normals.cbegin(); normal != definition->normals.cend(); ++normal)
				{
					bloodcell_preset << "\tmpFloat3<" << static_cast<int>(pow(10, precision) * normal->x) << ", "
						<< static_cast<int>(pow(10, precision) * normal->y) << ", " << static_cast<int>(pow(10, precision) * normal->z) << ", " 
						<< precision << ">" << (normal == std::prev(definition->normals.cend()) ? "" : ",") << "\n";
				}

				bloodcell_preset << ">;\n";
			}
		}
		definitionHeader << "	> ;\n}";
		bloodcell_preset << "\n}";
    }
}
