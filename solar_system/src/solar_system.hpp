#pragma once

#include <memory>
#include <vector>

#include "camera.hpp"
#include "planet.hpp"
#include "sun.hpp"

class SolarSystem
{
public:
    SolarSystem(unsigned int modeWidth, unsigned int modeHeight, const std::string& windowName);

    void run();

private:
    void update(float deltaTime);
    void speedUp();
    void slowDown();
    void togglePause();
    void updateBackgroundToFillView(const sf::View& view);

    sf::RenderWindow window_;
    Camera camera_;
    std::shared_ptr<Sun> sun_;
    sf::Texture backgroundTexture_;
    sf::Sprite background_;
    std::vector<std::shared_ptr<Planet>> solarSystemObjects_;
    float simulationSpeed_ = 0.004f;
    bool isPaused_ = false;
    int nextToFocusIndex_ = -1;
};
