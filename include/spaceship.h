#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <string>

#include "celestialobject.h"

class Spaceship : public CelestialObject {
private:
public:
    Spaceship(std::string name);
};

#endif
