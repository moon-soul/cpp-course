#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "entity.hpp"

class Camera
{
public:
    Camera(sf::RenderWindow& window);

    void update();
    void applyView();
    const sf::View& getView() const;
    void zoom(float factor);
    void transitionTo(std::shared_ptr<Entity> targetObject);

private:
    void move(const sf::Vector2f& direction, float speed);
    void handleMovement();

    sf::RenderWindow& window_;
    sf::View view_;
    float zoomLevel_ = 1.f;
    std::shared_ptr<Entity> targetObject_;
    bool transitioning_ = false;
    float transitionSpeed_ = 0.0025f;
    float movementSpeed_ = 0.25f;
};
