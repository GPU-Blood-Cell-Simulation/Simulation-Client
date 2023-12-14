//
//#include "../objects/bloodcellmodel.hpp"
#include "bloodcellmodel.hpp"
#include <string>
#include <format>
#include <fstream>

//
//void bloodcell::bloodCellModel::renderGUI(gui::GUIController& guiController, unsigned int modelIndex)
//{
//	
//}


void bloodcell::bloodCellModel::createHeaderFromData()
{
	std::ifstream template_definition_header("SimulationConfigData\\template_bloodcells_definition.hpp");
	std::ofstream definition_header("Config\\bloodcells_definition.hpp");
	definition_header << template_definition_header.rdbuf();

	int counter = 0;
	for (auto definition : predefinedModels)
	{
		definition_header << std::format("\r\n\tBloodCellDef<{}, {}, {},\n", definition.quantity, definition.vertices.size(), definition.indices.size());
		definition_header << std::format("\t\tpresets::{}_Springs\n", definition.name);
		definition_header << std::format("\t\tpresets::{}_Vertices\n", definition.name);
		definition_header << std::format("\t\tpresets::{}_Indices\n", definition.name);
		definition_header << std::format("\t\tpresets::{}_Normals>{}\n", definition.name, (counter + 1 == predefinedModels.size() ? "" : ","));
	}
	definition_header << "	> ;\n}";

	std::ifstream template_bloodcell_preset("SimulationConfigData\\template_blood_cell_presets.hpp");
	std::ofstream bloodcell_preset("Config\\blood_cell_presets.hpp");
	bloodcell_preset << template_bloodcell_preset.rdbuf();

	counter = 0;

}