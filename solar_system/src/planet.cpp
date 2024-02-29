#include "planet.hpp"

#include <algorithm>

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
    const auto sizeRatio = equatorialRadius_ / attractor_->getSize();
    setScale(sizeRatio);
}

void Planet::draw(sf::RenderWindow& window)
{
    sf::CircleShape orbit(orbitRadius_ + attractor_->getGlobalBounds().width / 2);
    const auto numPoints = std::max(200, static_cast<int>(orbitRadius_ / 5));
    orbit.setPointCount(numPoints);
    const auto& sunCenter = attractor_->getCenter();
    const auto& orbitGlobalBounds = orbit.getGlobalBounds();
    orbit.setPosition(sunCenter.x - orbitGlobalBounds.width / 2,
                      sunCenter.y - orbitGlobalBounds.height / 2);
    orbit.setFillColor(sf::Color::Transparent);
    orbit.setOutlineThickness(0.1);
    orbit.setOutlineColor(sf::Color::Yellow);
    window.draw(orbit);
    Entity::draw(window);
}
