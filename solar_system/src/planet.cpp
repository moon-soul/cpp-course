#include "planet.hpp"

Planet::Planet(const std::string& textureFilePath,
               const std::string& name,
               float radius,
               float distanceFromSun,
               float period,
               float angle,
               std::shared_ptr<CelestialBody> attractor)
    : CelestialBody(textureFilePath,
                    name,
                    radius,
                    distanceFromSun,
                    period,
                    angle,
                    attractor)
{
}
