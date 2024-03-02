#include "solar_system.hpp"

#include <algorithm>

#include "constants.hpp"
#include "moon.hpp"
#include "planet.hpp"
#include "sun.hpp"

SolarSystem::SolarSystem(unsigned int modeWidth, unsigned int modeHeight, const std::string& windowName)
    : window_(sf::VideoMode(modeWidth, modeHeight), windowName),
      camera_(window_)
{
    if (not backgroundTexture_.loadFromFile(FilePath::Assets::BACKGROUND))
    {
        throw std::runtime_error("Failed to load texture from file \"" + FilePath::Assets::BACKGROUND + '\"');
    }
    background_.setTexture(backgroundTexture_);
    const auto& windowSize = window_.getSize();
    background_.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));

    if (not soundBuffer_.loadFromFile(FilePath::Sounds::THEME))
    {
        throw std::runtime_error("Failed to load sound from file \"" + FilePath::Sounds::THEME + '\"');
    }
    sound_.setBuffer(soundBuffer_);
    sound_.setLoop(true);
    sound_.setVolume(5);
    sound_.play();

    const auto sun = std::make_shared<Sun>(FilePath::Assets::SUN, "Sun", modeWidth, modeHeight, 695500.f);
    const auto mercury = std::make_shared<Planet>(FilePath::Assets::MERCURY, "Mercury", 2440.f, 57.91f, 0.2f, 0.f, sun);
    const auto venus = std::make_shared<Planet>(FilePath::Assets::VENUS, "Venus", 6052.f, 108.21f, 0.6f, 0.f, sun);
    const auto earth = std::make_shared<Planet>(FilePath::Assets::EARTH, "Earth", 6378.f, 149.6f, 1.f, 0.f, sun);
    const auto mars = std::make_shared<Planet>(FilePath::Assets::MARS, "Mars", 3397.f, 227.94f, 1.9f, 0.f, sun);
    const auto jupiter = std::make_shared<Planet>(FilePath::Assets::JUPITER, "Jupiter", 71492.f, 778.41f, 11.9f, 0.f, sun);
    const auto saturn = std::make_shared<Planet>(FilePath::Assets::SATURN, "Saturn", 60268.f, 1426.73f, 29.5f, 0.f, sun);
    const auto uranus = std::make_shared<Planet>(FilePath::Assets::URANUS, "Uranus", 25559.f, 2870.97f, 84.f, 0.f, sun);
    const auto neptune = std::make_shared<Planet>(FilePath::Assets::NEPTUNE, "Neptune", 24764.f, 4498.25f, 164.8f, 0.f, sun);
    const auto moon = std::make_shared<Moon>(FilePath::Assets::MOON, "Moon", 1737.f, 0.3844f, 0.0748f, 0.f, earth);

    solarSystemObjects_.insert({"Sun", sun});
    solarSystemObjects_.insert({"Mercury", mercury});
    solarSystemObjects_.insert({"Venus", venus});
    solarSystemObjects_.insert({"Earth", earth});
    solarSystemObjects_.insert({"Mars", mars});
    solarSystemObjects_.insert({"Jupiter", jupiter});
    solarSystemObjects_.insert({"Saturn", saturn});
    solarSystemObjects_.insert({"Uranus", uranus});
    solarSystemObjects_.insert({"Neptune", neptune});
    solarSystemObjects_.insert({"Moon", moon});
}

void SolarSystem::run()
{
    sf::Clock clock;
    while (window_.isOpen())
    {
        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window_.close();
            }
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0)
                {
                    camera_.zoom(0.95f);
                }
                else if (event.mouseWheelScroll.delta < 0)
                {
                    camera_.zoom(1.05f);
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Left:
                    if (spacecraft_ == nullptr)
                    {
                        const auto& pixelPos = sf::Mouse::getPosition(window_);
                        const auto worldPos = window_.mapPixelToCoords(pixelPos);
                        spacecraft_ = std::make_shared<Spacecraft>(FilePath::Assets::SPACECRAFT,
                                                                   solarSystemObjects_,
                                                                   worldPos.x,
                                                                   worldPos.y);
                    }
                    break;
                case sf::Mouse::Right:
                    if (spacecraft_ != nullptr)
                    {
                        spacecraft_ = nullptr;
                    }
                    break;
                default:
                    break;
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Equal:
                    speedUp();
                    break;
                case sf::Keyboard::Dash:
                    slowDown();
                    break;
                case sf::Keyboard::Space:
                    togglePause();
                    break;
                case sf::Keyboard::C:
                    camera_.transitionTo(solarSystemObjects_["Sun"]);
                    break;
                case sf::Keyboard::V:
                    if (spacecraft_ != nullptr)
                    {
                        camera_.transitionTo(spacecraft_);
                    }
                    break;
                case sf::Keyboard::Num1:
                    camera_.transitionTo(solarSystemObjects_["Mercury"]);
                    break;
                case sf::Keyboard::Num2:
                    camera_.transitionTo(solarSystemObjects_["Venus"]);
                    break;
                case sf::Keyboard::Num3:
                    camera_.transitionTo(solarSystemObjects_["Earth"]);
                    break;
                case sf::Keyboard::Num4:
                    camera_.transitionTo(solarSystemObjects_["Mars"]);
                    break;
                case sf::Keyboard::Num5:
                    camera_.transitionTo(solarSystemObjects_["Jupiter"]);
                    break;
                case sf::Keyboard::Num6:
                    camera_.transitionTo(solarSystemObjects_["Saturn"]);
                    break;
                case sf::Keyboard::Num7:
                    camera_.transitionTo(solarSystemObjects_["Uranus"]);
                    break;
                case sf::Keyboard::Num8:
                    camera_.transitionTo(solarSystemObjects_["Neptune"]);
                    break;
                case sf::Keyboard::Num0:
                    camera_.transitionTo(solarSystemObjects_["Moon"]);
                    break;
                default:
                    break;
                }
            }
        }
        const auto deltaTime = clock.restart().asSeconds();
        camera_.update();
        updateBackgroundToFillView(camera_.getView());
        window_.clear();
        camera_.applyView();
        window_.draw(background_);
        update(deltaTime);
        draw();
        window_.display();
    }
}

void SolarSystem::update(float deltaTime)
{
    if (not isPaused_)
    {
        for (auto& [name, obj] : solarSystemObjects_)
        {
            obj->updatePosition(deltaTime, simulationSpeed_);
        }
        if (spacecraft_ != nullptr)
        {
            spacecraft_->updatePosition(deltaTime, simulationSpeed_);
        }
    }
}

void SolarSystem::draw()
{
    for (auto& [name, obj] : solarSystemObjects_)
    {
        obj->draw(window_);
    }
    if (spacecraft_ != nullptr)
    {
        spacecraft_->draw(window_);
    }
}

void SolarSystem::speedUp()
{
    constexpr auto maxSimulationSpeed = 0.8f;
    auto newSimulationSpeed = simulationSpeed_ + 0.005f;
    newSimulationSpeed = std::min(newSimulationSpeed, maxSimulationSpeed);
    simulationSpeed_ = newSimulationSpeed;
}

void SolarSystem::slowDown()
{
    constexpr auto minSimulationSpeed = -0.8f;
    auto newSimulationSpeed = simulationSpeed_ - 0.005f;
    newSimulationSpeed = std::max(newSimulationSpeed, minSimulationSpeed);
    simulationSpeed_ = newSimulationSpeed;
}

void SolarSystem::togglePause()
{
    isPaused_ = not isPaused_;
}

void SolarSystem::updateBackgroundToFillView(const sf::View& view)
{
    const auto& viewSize = view.getSize();
    const auto& localBounds = background_.getLocalBounds();
    background_.setScale(viewSize.x / localBounds.width,
                         viewSize.y / localBounds.height);

    const auto& viewCenter = view.getCenter();
    const auto& scale = background_.getScale();
    background_.setPosition(viewCenter.x - localBounds.width * scale.x / 2,
                            viewCenter.y - localBounds.height * scale.y / 2);
}
