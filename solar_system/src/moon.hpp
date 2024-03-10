#pragma once

#include "celestial_body.hpp"

class Moon : public CelestialBody
{
public:
    Moon(const std::string& textureFilePath,
         const std::string& name,
         float radius,
         float distanceFromPlanet,
         float period,
         float angle,
         std::shared_ptr<CelestialBody> attractor);
};
