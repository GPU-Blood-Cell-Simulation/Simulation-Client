#pragma once

#include "shader.hpp"

#include <memory>
#include <vector>

class SpringLines
{
public:
	SpringLines(unsigned int VBO);
	void draw(const Shader* shader) const;
private:
	std::vector<unsigned int> VAOs;
	std::vector<std::vector<unsigned int>> indexData;
};