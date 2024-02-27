#pragma once

#include <memory>

#include "celestial_body.hpp"
#include "sun.hpp"

class Planet : public CelestialBody
{
public:
    Planet(const std::string& textureFilePath,
           const std::string& name,
           float radius,
           float distanceFromSun,
           float period,
           float angle,
           std::shared_ptr<Sun> sun);

    void updatePosition(float deltaTime, float simulationSpeed) override final;
    void draw(sf::RenderWindow& window) override final;

private:
    std::shared_ptr<Sun> sun_;
};
