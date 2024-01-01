#pragma once

#include "blood_cell_presets.hpp"
#include "../objects/blood_cells_def_type.hpp"

#include <boost/mp11/list.hpp>


namespace
{
	using namespace boost::mp11;

	using UserDefinedBloodCellList = mp_list<
	BloodCellDef<15000, 20, 108,
		preset::RedBloodCell_One_Springs,
		preset::RedBloodCell_One_Vertices,
		preset::RedBloodCell_One_Indices,
		preset::RedBloodCell_One_Normals>
	> ;
}