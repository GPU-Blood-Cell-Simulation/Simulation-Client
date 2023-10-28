#include "simulation_instance.hpp"

namespace sim
{
	SimulationInstance::SimulationInstance(const serializable::ConfigData& configData) :
		bloodCellsModel(configData.bloodCellsDefinition),
		springLines(bloodCellsModel.getCudaOffsetBuffer(), configData.bloodCellsDefinition),
		veinModel(configData.veinDefinition)
	{}

	void SimulationInstance::drawParticles(const Shader* shader) const
	{
		bloodCellsModel.draw(shader);
	}

	void SimulationInstance::drawSpringLines(const Shader* shader) const
	{
		springLines.draw(shader);
	}

	void SimulationInstance::drawVein(const Shader* shader) const
	{
		veinModel.draw(shader);
	}
}
