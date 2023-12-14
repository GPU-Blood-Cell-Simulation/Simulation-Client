#pragma once

#include "blood_cell_presets.hpp"
#include "../objects/blood_cells_def_type.hpp"

#include <boost/mp11/list.hpp>


namespace
{
	using namespace boost::mp11;

	using UserDefinedBloodCellList = mp_list<
	BloodCellDef<500, 20, 108,
		presets::RedBloodCell_OneSprings
		presets::RedBloodCell_OneVertices
		presets::RedBloodCell_OneIndices
		presets::RedBloodCell_OneNormals
	> ;
}