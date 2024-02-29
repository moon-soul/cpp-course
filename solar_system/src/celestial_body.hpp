#pragma once

#include <memory>

#include "entity.hpp"

class CelestialBody : public Entity
{
public:
    CelestialBody(const std::string& textureFilePath,
                  const std::string& name,
                  float radius,
                  float distanceFromSun,
                  float period,
                  float angle,
                  std::shared_ptr<CelestialBody> attractor);

    float getSize() const;
    void updatePosition(float deltaTime, float simulationSpeed) override;

protected:
    std::string name_;
    float equatorialRadius_; // km
    float orbitRadius_; // km, millions
    float orbitPeriod_; // Earth years
    float currentOrbitAngle_; // degrees
    std::shared_ptr<CelestialBody> attractor_;
};
