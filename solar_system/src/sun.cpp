#include "sun.hpp"

Sun::Sun(const std::string& textureFilePath,
         const std::string& name,
         unsigned int modeWidth,
         unsigned int modeHeight,
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
    const auto& globalBounds = getGlobalBounds();
    const auto originX = (modeWidth - globalBounds.width) / 2;
    const auto originY = (modeHeight - globalBounds.height) / 2;
    setPosition(originX, originY);
}

void Sun::updatePosition(float deltaTime, float simulationSpeed)
{
    // TODO: move Sun around the center of the Milky Way galaxy
}
