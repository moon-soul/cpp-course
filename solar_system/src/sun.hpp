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
        float distanceFromAttractor,
        float period,
        float angle,
        std::shared_ptr<CelestialBody> attractor);
};
