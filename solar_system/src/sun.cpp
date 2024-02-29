#include "sun.hpp"

Sun::Sun(const std::string& textureFilePath,
         const std::string& name,
         unsigned int modeWidth,
         unsigned int modeHeight,
         float radius,
         float distanceFromAttractor,
         float period,
         float angle,
         std::shared_ptr<CelestialBody> attractor)
    : CelestialBody(textureFilePath,
                    name,
                    radius,
                    distanceFromAttractor,
                    period,
                    angle,
                    attractor)
{
    const auto& globalBounds = getGlobalBounds();
    const auto originX = (modeWidth - globalBounds.width) / 2;
    const auto originY = (modeHeight - globalBounds.height) / 2;
    setPosition(originX, originY);
}
