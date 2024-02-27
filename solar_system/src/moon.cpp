#include "moon.hpp"

Moon::Moon(const std::string& textureFilePath,
           const std::string& name,
           float radius,
           float distanceFromSun,
           float period,
           float angle)
    : CelestialBody(textureFilePath,
                    name,
                    radius,
                    distanceFromSun,
                    period,
                    angle)
{
}

void Moon::updatePosition(float deltaTime, float simulationSpeed)
{
    // TODO
}
