#include "vec_to_string.hpp"

#include <format>

std::ostream& operator<<(std::ostream& os, const glm::vec3& vec)
{
    os << std::format("static_cast<float>({}), static_cast<float>({}), static_cast<float>({})", vec.x, vec.y, vec.z);
    return os;
}
