#include <glm/glm.hpp>
#include <iostream>
#include "Util.h"

float Math::clamp(float val, float min, float max) {
    if (val > max) {
        return max;
    }

    if (val < min) {
        return min;
    }

    return val;
}

//@returns angle in degrees.
float Math::angle_between_vectors(glm::vec3 a, glm::vec3 b) {
    float dot = glm::dot(a, b);

    float AB = glm::length(a) * glm::length(b);

    float angle = glm::acos(dot / AB);

    return angle * 180 / PI;
}


glm::vec3 Math::lerp(glm::vec3 start, glm::vec3 end, float percent) {
    return (start + percent * (end - start));
}

glm::vec3 Math::GetUnitVector(glm::vec3 vec) {
    float len = glm::sqrt(glm::pow(vec.x, 2) + glm::pow(vec.y, 2) + glm::pow(vec.z, 2));
    return glm::vec3(vec.x / len, vec.y / len, vec.z / len);
}


void Math::PrintVector(glm::vec3 vec) {
    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}


bool Math::RealEquals(double real, double value, double delta) {
    return abs(real - value) <= delta;
}
