#include "vec_to_string.hpp"

std::ostream& operator<<(std::ostream& os, const glm::vec3& vec)
{
    os << "static_cast<float>(" << vec.x << "), static_cast<float>(" << vec.y << "), static_cast<float>(" << vec.z << ")";
    return os;
}
