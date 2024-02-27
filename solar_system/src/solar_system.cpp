#include "solar_system.hpp"

#include <algorithm>

#include "constants.hpp"

SolarSystem::SolarSystem(unsigned int modeWidth, unsigned int modeHeight, const std::string& windowName)
    : window_(sf::VideoMode(modeWidth, modeHeight), windowName),
      camera_(window_),
      sun_(std::make_shared<Sun>(FilePath::Assets::SUN, "SUN", modeWidth, modeHeight, 695500.f, 0.f, 0.f, 0.f))
{
    if (not backgroundTexture_.loadFromFile(FilePath::Assets::BACKGROUND))
    {
        throw std::runtime_error("Failed to load texture from file \"" + FilePath::Assets::BACKGROUND + '\"');
    }
    background_.setTexture(backgroundTexture_);
    const auto& windowSize = window_.getSize();
    background_.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));

    solarSystemObjects_.emplace_back(std::make_shared<Planet>(FilePath::Assets::MERCURY, "MERCURY", 2440.f, 57.91f, 0.2f, 0.f, sun_));
    solarSystemObjects_.emplace_back(std::make_shared<Planet>(FilePath::Assets::VENUS, "VENUS", 6052.f, 108.21f, 0.6f, 0.f, sun_));
    solarSystemObjects_.emplace_back(std::make_shared<Planet>(FilePath::Assets::EARTH, "EARTH", 6378.f, 149.6f, 1.f, 0.f, sun_));
    solarSystemObjects_.emplace_back(std::make_shared<Planet>(FilePath::Assets::MARS, "MARS", 3397.f, 227.94f, 1.9f, 0.f, sun_));
    solarSystemObjects_.emplace_back(std::make_shared<Planet>(FilePath::Assets::JUPITER, "JUPITER", 71492.f, 778.41f, 11.9f, 0.f, sun_));
    solarSystemObjects_.emplace_back(std::make_shared<Planet>(FilePath::Assets::SATURN, "SATURN", 60268.f, 1426.73f, 29.5f, 0.f, sun_));
    solarSystemObjects_.emplace_back(std::make_shared<Planet>(FilePath::Assets::URANUS, "URANUS", 25559.f, 2870.97f, 84.f, 0.f, sun_));
    solarSystemObjects_.emplace_back(std::make_shared<Planet>(FilePath::Assets::NEPTUNE, "NEPTUNE", 24764.f, 4498.25f, 164.8f, 0.f, sun_));
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
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Equal)
            {
                speedUp();
            }
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Dash)
            {
                slowDown();
            }
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Space)
            {
                togglePause();
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
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::C)
            {
                camera_.transitionTo(sun_);
                nextToFocusIndex_ = -1;
            }
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Q)
            {
                nextToFocusIndex_ = nextToFocusIndex_ > 0 ? --nextToFocusIndex_ : 0;
                camera_.transitionTo(solarSystemObjects_[nextToFocusIndex_]);
            }
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::E)
            {
                const int last = solarSystemObjects_.size() - 1;
                nextToFocusIndex_ = nextToFocusIndex_ < last ? ++nextToFocusIndex_ : last;
                camera_.transitionTo(solarSystemObjects_[nextToFocusIndex_]);
            }
        }
        const auto deltaTime = clock.restart().asSeconds();
        camera_.update();
        updateBackgroundToFillView(camera_.getView());
        window_.clear();
        camera_.applyView();
        window_.draw(background_);
        sun_->draw(window_);
        for (auto& obj : solarSystemObjects_)
        {
            update(deltaTime);
            obj->draw(window_);
        }
        window_.display();
    }
}

void SolarSystem::update(float deltaTime)
{
    if (not isPaused_)
    {
        for (auto& obj : solarSystemObjects_)
        {
            obj->updatePosition(deltaTime, simulationSpeed_);
        }
    }
}

void SolarSystem::speedUp()
{
    constexpr auto maxSimulationSpeed = 0.8f;
    auto newSimulationSpeed = simulationSpeed_ + 0.001f;
    newSimulationSpeed = std::min(newSimulationSpeed, maxSimulationSpeed);
    simulationSpeed_ = newSimulationSpeed;
}

void SolarSystem::slowDown()
{
    constexpr auto minSimulationSpeed = -0.8f;
    auto newSimulationSpeed = simulationSpeed_ - 0.001f;
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
