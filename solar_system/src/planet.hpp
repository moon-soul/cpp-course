#pragma once

#include "celestial_body.hpp"

class Planet : public CelestialBody
{
public:
    Planet(const std::string& textureFilePath,
           const std::string& name,
           float radius,
           float distanceFromSun,
           float period,
           float angle,
           std::shared_ptr<CelestialBody> attractor);
};
