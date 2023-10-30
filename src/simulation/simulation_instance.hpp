#pragma once

#include "../graphics/camera.hpp"
#include "../graphics/models/blood_cells_model.hpp"
#include "../graphics/models/spring_lines.hpp"
#include "../graphics/models/vein_model.hpp"
#include "../graphics/shader.hpp"
#include "../serializable/config_data.hpp"

namespace sim
{
	/// <summary>
	/// Carries all the models that represent a particular user-defined configuration. It contains all the model data necessary to render a frame.
	/// </summary>
	class SimulationInstance
	{
	public:
		SimulationInstance(const serializable::ConfigData& configData);
		void drawParticles(const Shader* shader) const;
		void drawSpringLines(const Shader* shader) const;
		void drawVein(const Shader* shader) const;

	private:
		graphics::BloodCellsModel bloodCellsModel;
		graphics::SpringLines springLines;
		graphics::VeinModel veinModel;
	};
}