#pragma once

#include "../objects/blood_cells_def_type.hpp"

#include <boost/mp11/list.hpp>
#include <boost/mp11/mpl_tuple.hpp>
#include <glm/vec3.hpp>

namespace preset
{
	using namespace boost::mp11;

using White_blood_cell_One_Springs = mp_list<
	Spring<8, 16, 5921527, 7>,
	Spring<0, 8, 3659710, 7>,
	Spring<16, 0, 3659710, 7>,
	Spring<8, 9, 3659692, 7>,
	Spring<4, 8, 5921527, 7>,
	Spring<9, 4, 3659710, 7>,
	Spring<12, 8, 5921527, 7>,
	Spring<0, 12, 3659710, 7>,
	Spring<12, 13, 3659692, 7>,
	Spring<1, 12, 5921527, 7>,
	Spring<13, 1, 3659710, 7>,
	Spring<16, 12, 5921527, 7>,
	Spring<16, 17, 3659692, 7>,
	Spring<2, 16, 5921527, 7>,
	Spring<17, 2, 3659710, 7>,
	Spring<1, 9, 5921527, 7>,
	Spring<8, 1, 3659710, 7>,
	Spring<1, 18, 3659710, 7>,
	Spring<5, 1, 5921538, 7>,
	Spring<18, 5, 3659710, 7>,
	Spring<2, 13, 5921527, 7>,
	Spring<12, 2, 3659710, 7>,
	Spring<2, 10, 3659710, 7>,
	Spring<3, 2, 5921538, 7>,
	Spring<10, 3, 3659710, 7>,
	Spring<4, 17, 5921527, 7>,
	Spring<16, 4, 3659710, 7>,
	Spring<4, 14, 3659710, 7>,
	Spring<6, 4, 5921538, 7>,
	Spring<14, 6, 3659710, 7>,
	Spring<5, 4, 5921538, 7>,
	Spring<9, 5, 3659710, 7>,
	Spring<5, 15, 3659710, 7>,
	Spring<14, 5, 5921527, 7>,
	Spring<15, 14, 3659692, 7>,
	Spring<11, 17, 5921527, 7>,
	Spring<6, 11, 3659710, 7>,
	Spring<17, 6, 3659710, 7>,
	Spring<11, 10, 3659692, 7>,
	Spring<2, 11, 5921527, 7>,
	Spring<19, 13, 5921527, 7>,
	Spring<3, 19, 3659710, 7>,
	Spring<13, 3, 3659710, 7>,
	Spring<19, 18, 3659692, 7>,
	Spring<1, 19, 5921527, 7>,
	Spring<7, 18, 5921527, 7>,
	Spring<19, 7, 3659710, 7>,
	Spring<18, 15, 5921527, 7>,
	Spring<7, 14, 5921527, 7>,
	Spring<15, 7, 3659710, 7>,
	Spring<14, 11, 5921527, 7>,
	Spring<7, 10, 5921527, 7>,
	Spring<11, 7, 3659710, 7>,
	Spring<10, 19, 5921527, 7>,
	Spring<8, 10, 9581231, 7>,
	Spring<9, 11, 9581231, 7>,
	Spring<12, 14, 9581231, 7>,
	Spring<13, 15, 9581231, 7>,
	Spring<16, 18, 9581231, 7>,
	Spring<17, 19, 9581231, 7>,
	Spring<0, 2, 5921538, 7>,
	Spring<2, 3, 5921538, 7>,
	Spring<3, 1, 5921538, 7>,
	Spring<1, 0, 5921538, 7>,
	Spring<6, 4, 5921538, 7>,
	Spring<4, 5, 5921538, 7>,
	Spring<5, 7, 5921538, 7>,
	Spring<7, 6, 5921538, 7>,
	Spring<0, 4, 5921538, 7>,
	Spring<1, 5, 5921538, 7>,
	Spring<2, 6, 5921538, 7>,
	Spring<3, 7, 5921538, 7>
>;

using White_blood_cell_One_Vertices = mp_list<
	mpFloat3<2960769, 2960769, -2960769, 7>,
	mpFloat3<2960769, -2960769, -2960769, 7>,
	mpFloat3<2960769, 2960769, 2960769, 7>,
	mpFloat3<2960769, -2960769, 2960769, 7>,
	mpFloat3<-2960769, 2960769, -2960769, 7>,
	mpFloat3<-2960769, -2960769, -2960769, 7>,
	mpFloat3<-2960769, 2960769, 2960769, 7>,
	mpFloat3<-2960769, -2960769, 2960769, 7>,
	mpFloat3<1829846, 0, -4790615, 7>,
	mpFloat3<-1829846, 0, -4790615, 7>,
	mpFloat3<1829846, 0, 4790615, 7>,
	mpFloat3<-1829846, 0, 4790615, 7>,
	mpFloat3<4790615, 1829846, 0, 7>,
	mpFloat3<4790615, -1829846, 0, 7>,
	mpFloat3<-4790615, 1829846, 0, 7>,
	mpFloat3<-4790615, -1829846, 0, 7>,
	mpFloat3<0, 4790615, -1829846, 7>,
	mpFloat3<0, 4790615, 1829846, 7>,
	mpFloat3<0, -4790615, -1829846, 7>,
	mpFloat3<0, -4790615, 1829846, 7>
>;

using White_blood_cell_One_Indices = mp_list<
	mp_int<8>, mp_int<16>, mp_int<0>,
	mp_int<8>, mp_int<9>, mp_int<4>,
	mp_int<12>, mp_int<8>, mp_int<0>,
	mp_int<12>, mp_int<13>, mp_int<1>,
	mp_int<16>, mp_int<12>, mp_int<0>,
	mp_int<16>, mp_int<17>, mp_int<2>,
	mp_int<1>, mp_int<9>, mp_int<8>,
	mp_int<1>, mp_int<18>, mp_int<5>,
	mp_int<2>, mp_int<13>, mp_int<12>,
	mp_int<2>, mp_int<10>, mp_int<3>,
	mp_int<4>, mp_int<17>, mp_int<16>,
	mp_int<4>, mp_int<14>, mp_int<6>,
	mp_int<5>, mp_int<4>, mp_int<9>,
	mp_int<5>, mp_int<15>, mp_int<14>,
	mp_int<11>, mp_int<17>, mp_int<6>,
	mp_int<11>, mp_int<10>, mp_int<2>,
	mp_int<19>, mp_int<13>, mp_int<3>,
	mp_int<19>, mp_int<18>, mp_int<1>,
	mp_int<7>, mp_int<18>, mp_int<19>,
	mp_int<15>, mp_int<5>, mp_int<18>,
	mp_int<7>, mp_int<14>, mp_int<15>,
	mp_int<11>, mp_int<6>, mp_int<14>,
	mp_int<7>, mp_int<10>, mp_int<11>,
	mp_int<19>, mp_int<3>, mp_int<10>,
	mp_int<8>, mp_int<4>, mp_int<16>,
	mp_int<12>, mp_int<1>, mp_int<8>,
	mp_int<16>, mp_int<2>, mp_int<12>,
	mp_int<1>, mp_int<5>, mp_int<9>,
	mp_int<2>, mp_int<3>, mp_int<13>,
	mp_int<4>, mp_int<6>, mp_int<17>,
	mp_int<5>, mp_int<14>, mp_int<4>,
	mp_int<11>, mp_int<2>, mp_int<17>,
	mp_int<19>, mp_int<1>, mp_int<13>,
	mp_int<7>, mp_int<15>, mp_int<18>,
	mp_int<7>, mp_int<11>, mp_int<14>,
	mp_int<7>, mp_int<19>, mp_int<10>
>;

using White_blood_cell_One_Normals = mp_list<
	mpFloat3<5773500, 5773500, -5773500, 7>,
	mpFloat3<4919500, -5859000, -6439800, 7>,
	mpFloat3<6439800, 4919500, 5859000, 7>,
	mpFloat3<6881999, -4253199, 5877699, 7>,
	mpFloat3<-5859000, 6439800, -4919500, 7>,
	mpFloat3<-6303700, -3895699, -6714699, 7>,
	mpFloat3<-5877699, 6881999, 4253199, 7>,
	mpFloat3<-5773500, -5773500, 5773500, 7>,
	mpFloat3<3484599, 2153300, -9122499, 7>,
	mpFloat3<-2628700, -1624400, -9510599, 7>,
	mpFloat3<2047500, -2530600, 9455400, 7>,
	mpFloat3<-3484599, 2153300, 9122499, 7>,
	mpFloat3<9122499, 3484599, -2153300, 7>,
	mpFloat3<8965100, -4232900, 1307899, 7>,
	mpFloat3<-9787999, 1742299, 1076700, 7>,
	mpFloat3<-8506399, -5257499, 0, 7>,
	mpFloat3<2153300, 9122499, -3484599, 7>,
	mpFloat3<-1307899, 8965100, 4232900, 7>,
	mpFloat3<-2530600, -9455400, -2047500, 7>,
	mpFloat3<2153300, -9122499, 3484599, 7>
>;


using Blood_dust_One_Springs = mp_list<
	Spring<1, 3, 3412007, 7>,
	Spring<1, 9, 3412060, 7>,
	Spring<1, 6, 3412023, 7>,
	Spring<1, 12, 3412079, 7>,
	Spring<1, 15, 3412111, 7>,
	Spring<1, 18, 3412035, 7>,
	Spring<3, 6, 3267436, 7>,
	Spring<6, 9, 3267490, 7>,
	Spring<9, 12, 3267491, 7>,
	Spring<12, 15, 3267437, 7>,
	Spring<15, 18, 3267490, 7>,
	Spring<18, 3, 3267425, 7>,
	Spring<3, 2, 2469448, 7>,
	Spring<6, 5, 2469435, 7>,
	Spring<9, 8, 2469462, 7>,
	Spring<12, 11, 2469446, 7>,
	Spring<15, 14, 2469393, 7>,
	Spring<18, 17, 2469482, 7>,
	Spring<2, 5, 5531449, 7>,
	Spring<5, 8, 5531510, 7>,
	Spring<8, 11, 5531476, 7>,
	Spring<11, 14, 5531449, 7>,
	Spring<14, 17, 5531510, 7>,
	Spring<17, 2, 5531476, 7>,
	Spring<2, 4, 3125652, 7>,
	Spring<5, 7, 3125634, 7>,
	Spring<8, 10, 3125602, 7>,
	Spring<11, 13, 3125600, 7>,
	Spring<14, 16, 3125585, 7>,
	Spring<17, 19, 3125605, 7>,
	Spring<4, 7, 3326058, 7>,
	Spring<7, 10, 3326029, 7>,
	Spring<10, 13, 3326151, 7>,
	Spring<13, 16, 3326097, 7>,
	Spring<16, 19, 3326029, 7>,
	Spring<19, 4, 3326114, 7>,
	Spring<4, 0, 3326085, 7>,
	Spring<7, 0, 3326158, 7>,
	Spring<10, 0, 3326183, 7>,
	Spring<13, 0, 3326188, 7>,
	Spring<16, 0, 3326140, 7>,
	Spring<19, 0, 3326138, 7>,
	Spring<2, 11, 11062945, 7>,
	Spring<5, 14, 11062922, 7>,
	Spring<8, 17, 11063005, 7>,
	Spring<3, 4, 3201504, 7>,
	Spring<6, 7, 3201551, 7>,
	Spring<9, 10, 3201490, 7>,
	Spring<12, 13, 3201538, 7>,
	Spring<15, 16, 3201490, 7>,
	Spring<18, 19, 3201476, 7>,
	Spring<1, 0, 2239658, 7>,
	Spring<1, 4, 3997861, 7>,
	Spring<1, 7, 3997890, 7>,
	Spring<1, 10, 3997897, 7>,
	Spring<1, 13, 3997962, 7>,
	Spring<1, 16, 3997952, 7>,
	Spring<1, 19, 3997922, 7>
>;

using Blood_dust_One_Vertices = mp_list<
	mpFloat3<7384, -1756000, 8000, 7>,
	mpFloat3<-2076, 483615, -2230, 7>,
	mpFloat3<-5533461, 456923, -2076, 7>,
	mpFloat3<-3273615, 1452538, -6615, 7>,
	mpFloat3<-3318692, -1748615, 7923, 7>,
	mpFloat3<-2767769, 446846, -4792461, 7>,
	mpFloat3<-1639923, 1446615, -2836307, 7>,
	mpFloat3<-1655692, -1754692, -2872538, 7>,
	mpFloat3<2763692, 470153, -4792615, 7>,
	mpFloat3<1627538, 1460384, -2836384, 7>,
	mpFloat3<1670307, -1740615, -2872615, 7>,
	mpFloat3<5529384, 503615, -2307, 7>,
	mpFloat3<3261230, 1480153, -6692, 7>,
	mpFloat3<3333384, -1720538, 7846, 7>,
	mpFloat3<2763692, 513692, 4788077, 7>,
	mpFloat3<1627538, 1486076, 2823000, 7>,
	mpFloat3<1670307, -1714461, 2888307, 7>,
	mpFloat3<-2767769, 490384, 4788231, 7>,
	mpFloat3<-1639923, 1472307, 2823000, 7>,
	mpFloat3<-1655692, -1728461, 2888384, 7>
>;

using Blood_dust_One_Indices = mp_list<
	mp_int<3>, mp_int<1>, mp_int<6>,
	mp_int<6>, mp_int<1>, mp_int<9>,
	mp_int<9>, mp_int<1>, mp_int<12>,
	mp_int<12>, mp_int<1>, mp_int<15>,
	mp_int<15>, mp_int<1>, mp_int<18>,
	mp_int<18>, mp_int<1>, mp_int<3>,
	mp_int<2>, mp_int<7>, mp_int<4>,
	mp_int<7>, mp_int<8>, mp_int<10>,
	mp_int<8>, mp_int<13>, mp_int<10>,
	mp_int<13>, mp_int<14>, mp_int<16>,
	mp_int<14>, mp_int<19>, mp_int<16>,
	mp_int<17>, mp_int<4>, mp_int<19>,
	mp_int<3>, mp_int<5>, mp_int<2>,
	mp_int<5>, mp_int<9>, mp_int<8>,
	mp_int<8>, mp_int<12>, mp_int<11>,
	mp_int<12>, mp_int<14>, mp_int<11>,
	mp_int<15>, mp_int<17>, mp_int<14>,
	mp_int<17>, mp_int<3>, mp_int<2>,
	mp_int<0>, mp_int<4>, mp_int<7>,
	mp_int<0>, mp_int<7>, mp_int<10>,
	mp_int<0>, mp_int<10>, mp_int<13>,
	mp_int<0>, mp_int<13>, mp_int<16>,
	mp_int<0>, mp_int<16>, mp_int<19>,
	mp_int<0>, mp_int<19>, mp_int<4>,
	mp_int<2>, mp_int<5>, mp_int<7>,
	mp_int<7>, mp_int<5>, mp_int<8>,
	mp_int<8>, mp_int<11>, mp_int<13>,
	mp_int<13>, mp_int<11>, mp_int<14>,
	mp_int<14>, mp_int<17>, mp_int<19>,
	mp_int<17>, mp_int<2>, mp_int<4>,
	mp_int<3>, mp_int<6>, mp_int<5>,
	mp_int<5>, mp_int<6>, mp_int<9>,
	mp_int<8>, mp_int<9>, mp_int<12>,
	mp_int<12>, mp_int<15>, mp_int<14>,
	mp_int<15>, mp_int<18>, mp_int<17>,
	mp_int<17>, mp_int<18>, mp_int<3>
>;

using Blood_dust_One_Normals = mp_list<
	mpFloat3<41999, -9999799, 44999, 7>,
	mpFloat3<-41999, 9999799, -44999, 7>,
	mpFloat3<-9890199, 1477999, -6999, 7>,
	mpFloat3<-1747999, 9845899, -44999, 7>,
	mpFloat3<-4793199, -8776299, 40000, 7>,
	mpFloat3<-4948199, 1460099, -8566399, 7>,
	mpFloat3<-895000, 9842699, -1523000, 7>,
	mpFloat3<-2378100, -8785200, -4143100, 7>,
	mpFloat3<4934900, 1501999, -8566799, 7>,
	mpFloat3<812000, 9849900, -1523000, 7>,
	mpFloat3<2451999, -8764899, -4142999, 7>,
	mpFloat3<9877200, 1562000, -6999, 7>,
	mpFloat3<1665100, 9860299, -44999, 7>,
	mpFloat3<4866800, -8735700, 40000, 7>,
	mpFloat3<4934900, 1580000, 8552799, 7>,
	mpFloat3<812000, 9863399, 1433099, 7>,
	mpFloat3<2451899, -8726699, 4222899, 7>,
	mpFloat3<-4948000, 1537999, 8552899, 7>,
	mpFloat3<-895000, 9856200, 1432999, 7>,
	mpFloat3<-2378000, -8747100, 4223000, 7>
>;

}