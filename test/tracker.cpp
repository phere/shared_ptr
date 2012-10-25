#include "tracker.hpp"

#include <iostream>

namespace
{
  static const bool printTracking = true;
}

size_t Tracker::created = 0;
size_t Tracker::alive = 0;

Tracker::Tracker(std::string _name)
  : name(_name)
  , id(++created)
{
  ++alive;
  if (printTracking) {
	std::cout << "Created Tracker #" << id
			  << " (\"" << name << "\")"
			  << " making " << alive << " alive."
			  << std::endl;
  }
}

Tracker::~Tracker()
{
  --alive;
  if (printTracking) {
	std::cout << "Destroyed Tracker #" << id
			  << " (\"" << name << "\")"
			  << " leaving " << alive << " alive."
			  << std::endl;
  }
}

std::string Tracker::getName() const
{
  return name;
}
