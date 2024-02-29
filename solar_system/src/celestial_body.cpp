#include "celestial_body.hpp"

#include <cmath>
#include <numbers>

CelestialBody::CelestialBody(const std::string& textureFilePath,
                             const std::string& name,
                             float radius,
                             float distanceFromSun,
                             float period,
                             float angle,
                             std::shared_ptr<CelestialBody> attractor)
    : Entity(textureFilePath),
      name_(name),
      equatorialRadius_(radius),
      orbitRadius_(distanceFromSun),
      orbitPeriod_(period),
      currentOrbitAngle_(angle),
      attractor_(attractor)
{
}

float CelestialBody::getSize() const
{
    return equatorialRadius_;
}

void CelestialBody::updatePosition(float deltaTime, float simulationSpeed)
{
    constexpr auto circleDegrees = 360.f;
    const auto orbitSpeed = circleDegrees / orbitPeriod_;
    currentOrbitAngle_ += -orbitSpeed * deltaTime * simulationSpeed;
    if (currentOrbitAngle_ > circleDegrees) currentOrbitAngle_ -= circleDegrees;

    const auto radAngle = currentOrbitAngle_ * (std::numbers::pi_v<float> / (circleDegrees / 2));

    const auto& attractorCenter = attractor_->getCenter();
    const auto& globalBounds = getGlobalBounds();
    const auto& attractorGlobalBounds = attractor_->getGlobalBounds();
    const auto halfAttractorX = attractorGlobalBounds.width / 2;
    const auto halfAttractorY = attractorGlobalBounds.height / 2;

    setPosition(attractorCenter.x - globalBounds.width / 2 + cos(radAngle) * (orbitRadius_ + halfAttractorX),
                attractorCenter.y - globalBounds.height / 2 + sin(radAngle) * (orbitRadius_ + halfAttractorY));
}
