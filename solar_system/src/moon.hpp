#pragma once

#include "celestial_body.hpp"

class Moon : public CelestialBody
{
public:
    Moon(const std::string& textureFilePath,
         const std::string& name,
         float radius,
         float distanceFromSun,
         float period,
         float angle);

    void updatePosition(float deltaTime, float simulationSpeed) override final;
};
