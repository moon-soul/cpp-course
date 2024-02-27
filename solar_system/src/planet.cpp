#include "planet.hpp"

#include <cmath>
#include <numbers>

Planet::Planet(const std::string& textureFilePath,
               const std::string& name,
               float radius,
               float distanceFromSun,
               float period,
               float angle,
               std::shared_ptr<Sun> sun)
    : CelestialBody(textureFilePath,
                    name,
                    radius,
                    distanceFromSun,
                    period,
                    angle),
      sun_(sun)
{
    const auto sizeRatio = equatorialRadius_ / sun_->getSize();
    setScale(sizeRatio);
}

void Planet::updatePosition(float deltaTime, float simulationSpeed)
{
    constexpr auto circleDegrees = 360.f;
    const auto orbitSpeed = circleDegrees / orbitPeriod_;
    currentOrbitAngle_ += -orbitSpeed * deltaTime * simulationSpeed;
    if (currentOrbitAngle_ > circleDegrees) currentOrbitAngle_ -= circleDegrees;

    const auto radAngle = currentOrbitAngle_ * (std::numbers::pi_v<float> / (circleDegrees / 2));

    const auto& sunCenter = sun_->getCenter();
    const auto& globalBounds = getGlobalBounds();
    const auto& sunGlobalBounds = sun_->getGlobalBounds();
    const auto halfSunX = sunGlobalBounds.width / 2;
    const auto halfSunY = sunGlobalBounds.height / 2;

    setPosition(sunCenter.x - globalBounds.width / 2 + cos(radAngle) * (orbitRadius_ + halfSunX),
                sunCenter.y - globalBounds.height / 2 + sin(radAngle) * (orbitRadius_ + halfSunY));
}

void Planet::draw(sf::RenderWindow& window)
{
    sf::CircleShape orbit(orbitRadius_ + sun_->getGlobalBounds().width / 2);
    const auto numPoints = std::max(200, static_cast<int>(orbitRadius_ / 5));
    orbit.setPointCount(numPoints);
    const auto& sunCenter = sun_->getCenter();
    const auto& orbitGlobalBounds = orbit.getGlobalBounds();
    orbit.setPosition(sunCenter.x - orbitGlobalBounds.width / 2,
                      sunCenter.y - orbitGlobalBounds.height / 2);
    orbit.setFillColor(sf::Color::Transparent);
    orbit.setOutlineThickness(0.1);
    orbit.setOutlineColor(sf::Color::Yellow);
    window.draw(orbit);
    Entity::draw(window);
}
