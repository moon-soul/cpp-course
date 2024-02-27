#pragma once

#include <vector>

#include "entity.hpp"

class CelestialBody : public Entity
{
public:
    CelestialBody(const std::string& textureFilePath,
                  const std::string& name,
                  float radius,
                  float distanceFromSun,
                  float period,
                  float angle);

    float getSize() const;
    void updatePosition(float deltaTime, float simulationSpeed) override = 0;

protected:
    std::string name_;
    float equatorialRadius_; // km
    float orbitRadius_; // km, millions
    float orbitPeriod_; // Earth years
    float currentOrbitAngle_; // degrees
};
