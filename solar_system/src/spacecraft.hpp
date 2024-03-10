#pragma once

#include <deque>
#include <map>

#include "celestial_body.hpp"
#include "entity.hpp"

class Spacecraft : public Entity
{
public:
    Spacecraft(const std::string& textureFilePath,
               const std::map<std::string, std::shared_ptr<CelestialBody>>& solarSystemObjects,
               float x,
               float y);

    void draw(sf::RenderWindow& window) override;
    void updatePosition(float deltaTime, float simulationSpeed) override;

private:
    const std::map<std::string, std::shared_ptr<CelestialBody>>& solarSystemObjects_;
    sf::Vector2f velocity_;
    std::deque<sf::Vector2f> trailPoints_;
    static constexpr auto maxTrailLength_ = 1000u;
    static constexpr auto updateInterval_ = 100u;
    uint16_t updateCounter_ = 0;
};
