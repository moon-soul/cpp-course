#pragma once

#include "celestial_body.hpp"

class Sun : public CelestialBody
{
public:
    Sun(const std::string& textureFilePath,
        const std::string& name,
        unsigned int modeWidth,
        unsigned int modeHeight,
        float radius,
        float distanceFromAttractor = 0.f,
        float period = 0.f,
        float angle = 0.f,
        std::shared_ptr<CelestialBody> attractor = nullptr);
};
