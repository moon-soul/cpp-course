#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class Entity
{
public:
    Entity(const std::string& textureFilePath);
    virtual ~Entity() = default;

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getCenter() const;
    const sf::Sprite& getSprite() const;
    float getScale() const;
    void setPosition(float x, float y);
    void setScale(float scaleFactor);
    virtual void draw(sf::RenderWindow& window);

    virtual void updatePosition(float deltaTime, float simulationSpeed) = 0; // TODO: spacecraft

protected:
    sf::Texture texture_;
    sf::Sprite sprite_;
};
