#ifndef PHERE_SMART_PTR_TEST_TRACKER_HPP
#define PHERE_SMART_PTR_TEST_TRACKER_HPP

#include <string>

struct Tracker
{
  Tracker(std::string _name);

  ~Tracker();

  std::string getName() const;

private:
  static size_t created;
  static size_t alive;

  const std::string name;
  const size_t id;
};

#endif
