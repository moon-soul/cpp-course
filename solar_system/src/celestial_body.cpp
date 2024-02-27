#include "celestial_body.hpp"

CelestialBody::CelestialBody(const std::string& textureFilePath,
                             const std::string& name,
                             float radius,
                             float distanceFromSun,
                             float period,
                             float angle)
    : Entity(textureFilePath),
      name_(name),
      equatorialRadius_(radius),
      orbitRadius_(distanceFromSun),
      orbitPeriod_(period),
      currentOrbitAngle_(angle)
{
}

float CelestialBody::getSize() const
{
    return equatorialRadius_;
}
