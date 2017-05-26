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

float Math::angle_between_vectors(glm::vec3 a, glm::vec3 b) {
    float dot = glm::dot(a, b);

    float AB = glm::length(a) * glm::length(b);

    float angle = glm::acos(dot / AB);

    return angle * 180 / PI;
}


glm::vec3 Math::lerp(glm::vec3 start, glm::vec3 end, float percent) {
    return (start + percent * (end - start));
}