#define BOOST_TEST_MODULE shared_ptr
#include <boost/test/unit_test.hpp>

#include <phere/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <iostream>
#include <string>

#include "tracker.hpp"

BOOST_AUTO_TEST_CASE( usage )
{
  typedef phere::shared_ptr<Tracker> TrackerPtr;

  TrackerPtr p1(boost::make_shared<Tracker>("p1"));
  TrackerPtr p2(p1);
  TrackerPtr p3 = p2;

  BOOST_CHECK_EQUAL(p1, p2);
  BOOST_CHECK(p2.pointsToSameObject(p3));

  BOOST_CHECK(p3); // conversion to bool
  BOOST_CHECK_EQUAL(p3->getName(), "p1");
  p3.reset();
  BOOST_CHECK(!p3);
}
