// **************************************************************************************************************************
// build command: clang++ main.cpp -o sfml-app -std=c++20 -Wall -Wextra -pedantic -lsfml-graphics -lsfml-window -lsfml-system
// **************************************************************************************************************************

#include <SFML/Graphics.hpp>

int main()
{
    sf::Texture texture;
    if (not texture.loadFromFile("image.png"))
    {
        return -1;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "C++ for GameDev");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}
