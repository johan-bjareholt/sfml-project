#ifndef PLANET_H
#define PLANET_H

#include <string>

#include "celestialobject.h"

class Planet : public CelestialObject {
private:
public:
    Planet(float radius, float mass, std::string name);
};

#endif
