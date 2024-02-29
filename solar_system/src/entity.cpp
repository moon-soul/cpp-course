#include "entity.hpp"

#include <stdexcept>

Entity::Entity(const std::string& textureFilePath)
{
    if (not texture_.loadFromFile(textureFilePath))
    {
        throw std::runtime_error("Failed to load texture from file \"" + textureFilePath + '\"');
    }
    sprite_.setTexture(texture_);
}

sf::Vector2f Entity::getPosition() const
{
    return sprite_.getPosition();
}

sf::FloatRect Entity::getGlobalBounds() const
{
    return sprite_.getGlobalBounds();
}

sf::Vector2f Entity::getCenter() const
{
    sf::Vector2f center;
    const auto& position = getPosition();
    const auto& globalBounds = getGlobalBounds();
    center.x = position.x + globalBounds.width / 2;
    center.y = position.y + globalBounds.height / 2;
    return center;
}

const sf::Sprite& Entity::getSprite() const
{
    return sprite_;
}

float Entity::getScale() const
{
    return sprite_.getScale().x;
}

void Entity::setPosition(float x, float y)
{
    sprite_.setPosition(x, y);
}

void Entity::setScale(float scaleFactor)
{
    sprite_.setScale(scaleFactor, scaleFactor);
}

void Entity::draw(sf::RenderWindow& window)
{
    window.draw(sprite_);
}
