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

    const auto SUN = std::make_shared<Sun>(FilePath::Assets::SUN, "SUN", modeWidth, modeHeight, 695500.f);
    const auto MERCURY = std::make_shared<Planet>(FilePath::Assets::MERCURY, "MERCURY", 2440.f, 57.91f, 0.2f, 0.f, SUN);
    const auto VENUS = std::make_shared<Planet>(FilePath::Assets::VENUS, "VENUS", 6052.f, 108.21f, 0.6f, 0.f, SUN);
    const auto EARTH = std::make_shared<Planet>(FilePath::Assets::EARTH, "EARTH", 6378.f, 149.6f, 1.f, 0.f, SUN);
    const auto MARS = std::make_shared<Planet>(FilePath::Assets::MARS, "MARS", 3397.f, 227.94f, 1.9f, 0.f, SUN);
    const auto JUPITER = std::make_shared<Planet>(FilePath::Assets::JUPITER, "JUPITER", 71492.f, 778.41f, 11.9f, 0.f, SUN);
    const auto SATURN = std::make_shared<Planet>(FilePath::Assets::SATURN, "SATURN", 60268.f, 1426.73f, 29.5f, 0.f, SUN);
    const auto URANUS = std::make_shared<Planet>(FilePath::Assets::URANUS, "URANUS", 25559.f, 2870.97f, 84.f, 0.f, SUN);
    const auto NEPTUNE = std::make_shared<Planet>(FilePath::Assets::NEPTUNE, "NEPTUNE", 24764.f, 4498.25f, 164.8f, 0.f, SUN);
    const auto MOON = std::make_shared<Moon>(FilePath::Assets::MOON, "MOON", 1737.f, 0.3844f, 0.0748f, 0.f, EARTH);

    solarSystemObjects_.insert({"SUN", SUN});
    solarSystemObjects_.insert({"MERCURY", MERCURY});
    solarSystemObjects_.insert({"VENUS", VENUS});
    solarSystemObjects_.insert({"EARTH", EARTH});
    solarSystemObjects_.insert({"MARS", MARS});
    solarSystemObjects_.insert({"JUPITER", JUPITER});
    solarSystemObjects_.insert({"SATURN", SATURN});
    solarSystemObjects_.insert({"URANUS", URANUS});
    solarSystemObjects_.insert({"NEPTUNE", NEPTUNE});
    solarSystemObjects_.insert({"MOON", MOON});
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
                    camera_.transitionTo(solarSystemObjects_["SUN"]);
                    break;
                case sf::Keyboard::V:
                    if (spacecraft_ != nullptr)
                    {
                        camera_.transitionTo(spacecraft_);
                    }
                    break;
                case sf::Keyboard::Num1:
                    camera_.transitionTo(solarSystemObjects_["MERCURY"]);
                    break;
                case sf::Keyboard::Num2:
                    camera_.transitionTo(solarSystemObjects_["VENUS"]);
                    break;
                case sf::Keyboard::Num3:
                    camera_.transitionTo(solarSystemObjects_["EARTH"]);
                    break;
                case sf::Keyboard::Num4:
                    camera_.transitionTo(solarSystemObjects_["MARS"]);
                    break;
                case sf::Keyboard::Num5:
                    camera_.transitionTo(solarSystemObjects_["JUPITER"]);
                    break;
                case sf::Keyboard::Num6:
                    camera_.transitionTo(solarSystemObjects_["SATURN"]);
                    break;
                case sf::Keyboard::Num7:
                    camera_.transitionTo(solarSystemObjects_["URANUS"]);
                    break;
                case sf::Keyboard::Num8:
                    camera_.transitionTo(solarSystemObjects_["NEPTUNE"]);
                    break;
                case sf::Keyboard::Num0:
                    camera_.transitionTo(solarSystemObjects_["MOON"]);
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
