#pragma once

#include <glm/glm.hpp>

namespace Math{
    # define PI 3.1415926535897932384

    float clamp(float val, float min, float max);

    float angle_between_vectors(glm::vec3 a, glm::vec3 b);

    glm::vec3 lerp(glm::vec3 start, glm::vec3 end, float percent);
}
