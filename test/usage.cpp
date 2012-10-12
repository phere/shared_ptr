#define BOOST_TEST_MODULE smart_ptr
#include <boost/test/unit_test.hpp>

#include <phere/shared_ptr.hpp>

#include <iostream>
#include <string>

struct Tracker
{
  Tracker(std::string _name)
    : name(_name)
    , id(++created)
  {
    ++alive;
    std::cout << "Created Tracker #" << id
	      << " (\"" << name << "\")"
	      << " making " << alive << " alive."
	      << std::endl;
  }

  ~Tracker()
  {
    --alive;
    std::cout << "Destroyed Tracker #" << id
	      << " (\"" << name << "\")"
	      << " leaving " << alive << " alive."
	      << std::endl;
  }

private:
  static size_t created;
  static size_t alive;

  const std::string name;
  const size_t id;
};
size_t Tracker::created = 0;
size_t Tracker::alive = 0;


BOOST_AUTO_TEST_CASE( usage )
{
  Tracker tracker("Foo");
}
