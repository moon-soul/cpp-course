#include "moon.hpp"

Moon::Moon(const std::string& textureFilePath,
           const std::string& name,
           float radius,
           float distanceFromPlanet,
           float period,
           float angle,
           std::shared_ptr<CelestialBody> attractor)
    : CelestialBody(textureFilePath,
                    name,
                    radius,
                    distanceFromPlanet,
                    period,
                    angle,
                    attractor)
{
}
