#pragma once

#include <map>

#include "camera.hpp"
#include "celestial_body.hpp"

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
    float simulationSpeed_ = 0.004f;
    bool isPaused_ = false;
};
