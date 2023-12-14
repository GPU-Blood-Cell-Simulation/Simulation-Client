#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <utility>
#include <string>

namespace bloodcell
{
	struct bloodCellModel_data
	{
		std::vector<glm::vec3> vertices;
		std::vector<unsigned int> indices;
		std::vector<glm::vec3> normals;
		std::vector<std::pair<int, int>> springs;
		unsigned int modelSize;
		float scale = 1.0f;
		std::string name;
		int quantity;

		bloodCellModel_data() {}
		bloodCellModel_data(std::vector<glm::vec3> _vertices, std::vector<unsigned int> _indices,
			std::vector<glm::vec3> _normals, std::vector<std::pair<int, int>> _springs, std::string _name, int _quantity) :
			modelSize(_vertices.size()), indices(_indices), vertices(_vertices), normals(_normals),
			springs(_springs), name(_name), quantity(_quantity) {}

	};

	class bloodCellModel
	{
	public:
		
		static void createHeaderFromData(int decimalPrecision);

		inline static std::vector<bloodCellModel_data> predefinedModels = std::vector<bloodCellModel_data>({
			bloodCellModel_data(
				std::vector<glm::vec3>({ glm::vec3(0.00096, -0.22828, 0.00104), glm::vec3(-0.00027, 0.06287, -0.00029), glm::vec3(-0.71935, 0.05940, -0.00027), glm::vec3(-0.42557, 0.18883, -0.00086), glm::vec3(-0.43143, -0.22732, 0.00103), glm::vec3(-0.35981, 0.05809, -0.62302), glm::vec3(-0.21319, 0.18806, -0.36872), glm::vec3(-0.21524, -0.22811, -0.37343), glm::vec3(0.35928, 0.06112, -0.62304), glm::vec3(0.21158, 0.18985, -0.36873), glm::vec3(0.21714, -0.22628, -0.37344), glm::vec3(0.71882, 0.06547, -0.00030), glm::vec3(0.42396, 0.19242, -0.00087), glm::vec3(0.43334, -0.22367, 0.00102), glm::vec3(0.35928, 0.06678, 0.62245), glm::vec3(0.21158, 0.19319, 0.36699), glm::vec3(0.21714, -0.22288, 0.37548), glm::vec3(-0.35981, 0.06375, 0.62247), glm::vec3(-0.21319, 0.19140, 0.36699), glm::vec3(-0.21524, -0.22470, 0.37549) }),
				std::vector<unsigned int>({ 3, 1, 6, 6, 1, 9, 9, 1, 12, 12, 1, 15, 15, 1, 18, 18, 1, 3, 2, 7, 4, 7, 8, 10, 8, 13, 10, 13, 14, 16, 14, 19, 16, 17, 4, 19, 3, 5, 2, 5, 9, 8, 8, 12, 11, 12, 14, 11, 15, 17, 14, 17, 3, 2, 0, 4, 7, 0, 7, 10, 0, 10, 13, 0, 13, 16, 0, 16, 19, 0, 19, 4, 2, 5, 7, 7, 5, 8, 8, 11, 13, 13, 11, 14, 14, 17, 19, 17, 2, 4, 3, 6, 5, 5, 6, 9, 8, 9, 12, 12, 15, 14, 15, 18, 17, 17, 18, 3 }),
				std::vector<glm::vec3>({ glm::vec3(0.00420, -0.99998, 0.00450), glm::vec3(-0.00420, 0.99998, -0.00450), glm::vec3(-0.98902, 0.14780, -0.00070), glm::vec3(-0.17480, 0.98459, -0.00450), glm::vec3(-0.47932, -0.87763, 0.00400), glm::vec3(-0.49482, 0.14601, -0.85664), glm::vec3(-0.08950, 0.98427, -0.15230), glm::vec3(-0.23781, -0.87852, -0.41431), glm::vec3(0.49349, 0.15020, -0.85668), glm::vec3(0.08120, 0.98499, -0.15230), glm::vec3(0.24520, -0.87649, -0.41430), glm::vec3(0.98772, 0.15620, -0.00070), glm::vec3(0.16651, 0.98603, -0.00450), glm::vec3(0.48668, -0.87357, 0.00400), glm::vec3(0.49349, 0.15800, 0.85528), glm::vec3(0.08120, 0.98634, 0.14331), glm::vec3(0.24519, -0.87267, 0.42229), glm::vec3(-0.49480, 0.15380, 0.85529), glm::vec3(-0.08950, 0.98562, 0.14330), glm::vec3(-0.23780, -0.87471, 0.42230) }),
				std::vector<std::pair<int, int>>({ std::make_pair(1, 3), std::make_pair(1, 9), std::make_pair(1, 6), std::make_pair(1, 12), std::make_pair(1, 15), std::make_pair(1, 18), std::make_pair(3, 6), std::make_pair(6, 9), std::make_pair(9, 12), std::make_pair(12, 15), std::make_pair(15, 18), std::make_pair(18, 3), std::make_pair(3, 2), std::make_pair(6, 5), std::make_pair(9, 8), std::make_pair(12, 11), std::make_pair(15, 14), std::make_pair(18, 17), std::make_pair(2, 5), std::make_pair(5, 8), std::make_pair(8, 11), std::make_pair(11, 14), std::make_pair(14, 17), std::make_pair(17, 2), std::make_pair(2, 4), std::make_pair(5, 7), std::make_pair(8, 10), std::make_pair(11, 13), std::make_pair(14, 16), std::make_pair(17, 19), std::make_pair(4, 7), std::make_pair(7, 10), std::make_pair(10, 13), std::make_pair(13, 16), std::make_pair(16, 19), std::make_pair(19, 4), std::make_pair(4, 0), std::make_pair(7, 0), std::make_pair(10, 0), std::make_pair(13, 0), std::make_pair(16, 0), std::make_pair(19, 0), std::make_pair(2, 11), std::make_pair(5, 14), std::make_pair(8, 17), std::make_pair(3, 4), std::make_pair(6, 7), std::make_pair(9, 10), std::make_pair(12, 13), std::make_pair(15, 16), std::make_pair(18, 19), std::make_pair(1, 0), std::make_pair(1, 4), std::make_pair(1, 7), std::make_pair(1, 10), std::make_pair(1, 13), std::make_pair(1, 16), std::make_pair(1, 19) }),
				"RedBloodCell_One",
				5000
			)
		});

	};
}