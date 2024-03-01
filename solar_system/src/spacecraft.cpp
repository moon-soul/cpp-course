#include "spacecraft.hpp"

#include <cmath>

Spacecraft::Spacecraft(const std::string& textureFilePath,
                       const std::map<std::string, std::shared_ptr<CelestialBody>>& solarSystemObjects,
                       float x,
                       float y)
    : Entity(textureFilePath),
      solarSystemObjects_(solarSystemObjects)
{
    setScale(0.005);
    const auto& globalBounds = getGlobalBounds();
    setPosition(x - globalBounds.width / 2, y - globalBounds.height / 2);
}

void Spacecraft::draw(sf::RenderWindow& window)
{
    sf::VertexArray trail(sf::LineStrip, trailPoints_.size());
    auto i = 0u;
    for (const auto& point : trailPoints_)
    {
        trail[i].position = point;
        const auto alpha = 255 * (1 - static_cast<float>(i) / maxTrailLength_);
        trail[i].color = sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha));
        ++i;
    }
    window.draw(trail);
    Entity::draw(window);
}

void Spacecraft::updatePosition(float deltaTime, float simulationSpeed)
{
    constexpr auto minDistance = 10.f;

    deltaTime *= simulationSpeed;

    sf::Vector2f totalAcceleration(0.f, 0.f);

    for (const auto& [name, obj] : solarSystemObjects_)
    {
        const auto& objPosition = obj->getCenter();
        const auto& position = getCenter();

        const auto dx = objPosition.x - position.x;
        const auto dy = objPosition.y - position.y;
        const auto distance = std::sqrt(dx * dx + dy * dy);

        if (distance < minDistance)
        {
            continue;
        }

        const auto forceMagnitude = 1000.f / (distance * distance);
        const sf::Vector2f forceDirection(dx / distance, dy / distance);
        const auto acceleration = forceDirection * forceMagnitude;

        totalAcceleration += acceleration;
    }

    velocity_ += totalAcceleration * deltaTime;
    const auto newPosition = getPosition() + velocity_;
    setPosition(newPosition.x, newPosition.y);

    if (++updateCounter_ >= updateInterval_)
    {
        updateCounter_ = 0;
        trailPoints_.push_front(getCenter());
        if (trailPoints_.size() > maxTrailLength_)
        {
            trailPoints_.pop_back();
        }
    }
}
