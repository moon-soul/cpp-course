#include "celestial_body.hpp"

#include <algorithm>
#include <cmath>
#include <numbers>

CelestialBody::CelestialBody(const std::string& textureFilePath,
                             const std::string& name,
                             float radius,
                             float distanceFromAttractor,
                             float period,
                             float angle,
                             std::shared_ptr<CelestialBody> attractor)
    : Entity(textureFilePath),
      name_(name),
      equatorialRadius_(radius),
      orbitRadius_(distanceFromAttractor),
      orbitPeriod_(period),
      currentOrbitAngle_(angle),
      attractor_(attractor)
{
    if (attractor_ != nullptr)
    {
        const auto sizeRatio = equatorialRadius_ * attractor_->getScale() / attractor_->getSize();
        setScale(sizeRatio);
    }
}

float CelestialBody::getSize() const
{
    return equatorialRadius_;
}

void CelestialBody::draw(sf::RenderWindow& window)
{
    if (attractor_ != nullptr)
    {
        sf::CircleShape orbit(orbitRadius_ + attractor_->getGlobalBounds().width / 2);
        const auto numPoints = std::max(200, static_cast<int>(orbitRadius_ / 5));
        orbit.setPointCount(numPoints);
        const auto& attractorCenter = attractor_->getCenter();
        const auto& orbitGlobalBounds = orbit.getGlobalBounds();
        orbit.setPosition(attractorCenter.x - orbitGlobalBounds.width / 2,
                          attractorCenter.y - orbitGlobalBounds.height / 2);
        orbit.setFillColor(sf::Color::Transparent);
        orbit.setOutlineThickness(0.1);
        orbit.setOutlineColor(sf::Color::Yellow);
        window.draw(orbit);
    }
    Entity::draw(window);
}

void CelestialBody::updatePosition(float deltaTime, float simulationSpeed)
{
    if (attractor_ == nullptr)
    {
        return;
    }
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
