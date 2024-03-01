#pragma once

#include <map>

#include "camera.hpp"
#include "celestial_body.hpp"
#include "spacecraft.hpp"

class SolarSystem
{
public:
    SolarSystem(unsigned int modeWidth, unsigned int modeHeight, const std::string& windowName);

    void run();

private:
    void update(float deltaTime);
    void draw();
    void speedUp();
    void slowDown();
    void togglePause();
    void updateBackgroundToFillView(const sf::View& view);

    sf::RenderWindow window_;
    Camera camera_;
    sf::Texture backgroundTexture_;
    sf::Sprite background_;
    std::map<std::string, std::shared_ptr<CelestialBody>> solarSystemObjects_;
    std::shared_ptr<Spacecraft> spacecraft_ = nullptr;
    float simulationSpeed_ = 0.005f;
    bool isPaused_ = false;
};
