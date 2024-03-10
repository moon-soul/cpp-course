#include "camera.hpp"

#include <algorithm>
#include <cmath>

Camera::Camera(sf::RenderWindow& window)
    : window_(window),
      view_(window_.getDefaultView())
{
}

void Camera::update()
{
    handleMovement();

    if (transitioning_)
    {
        const auto& currentPosition = view_.getCenter();
        const auto direction = targetObject_->getCenter() - currentPosition;
        move(direction, transitionSpeed_);
    }
}

void Camera::applyView()
{
    window_.setView(view_);
}

const sf::View& Camera::getView() const
{
    return view_;
}

void Camera::zoom(float factor)
{
    constexpr auto minZoomLevel = 0.01f;
    constexpr auto maxZoomLevel = 5.f;
    constexpr auto minTransitionSpeed = 0.0025f;
    constexpr auto maxTransitionSpeed = 0.02f;

    auto newZoomLevel = zoomLevel_ * factor;
    auto newTransitionSpeed = transitionSpeed_ /= factor;

    newZoomLevel = std::clamp(newZoomLevel, minZoomLevel, maxZoomLevel);
    newTransitionSpeed = std::clamp(newTransitionSpeed, minTransitionSpeed, maxTransitionSpeed);

    factor = newZoomLevel / zoomLevel_;
    view_.zoom(factor);

    zoomLevel_ = newZoomLevel;
    transitionSpeed_ = newTransitionSpeed;
    movementSpeed_ *= factor;
}

void Camera::transitionTo(std::shared_ptr<Entity> targetObject)
{
    targetObject_ = targetObject;
    transitioning_ = true;
}

void Camera::move(const sf::Vector2f& direction, float speed)
{
    const auto movement = direction * speed;
    view_.move(movement);
}

void Camera::handleMovement()
{
    sf::Vector2f movementDirection(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        movementDirection.y -= 1;
        transitioning_ = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        movementDirection.y += 1;
        transitioning_ = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        movementDirection.x -= 1;
        transitioning_ = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        movementDirection.x += 1;
        transitioning_ = false;
    }

    if (movementDirection.x != 0.f or movementDirection.y != 0.f)
    {
        const auto magnitude = std::sqrt(movementDirection.x * movementDirection.x + movementDirection.y * movementDirection.y);
        movementDirection /= magnitude;
    }

    move(movementDirection, movementSpeed_);
}
