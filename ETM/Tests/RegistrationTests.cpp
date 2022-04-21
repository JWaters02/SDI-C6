#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Application/RegistrationCheck.h"

BOOST_AUTO_TEST_SUITE(RegistrationTests)

    BOOST_AUTO_TEST_CASE(ValidRegistration) {
        RegistrationCheck check = RegistrationCheck("3 PCW");
        BOOST_CHECK(check.getResponse());
    }

    BOOST_AUTO_TEST_CASE(InvalidRegistration) {
        RegistrationCheck check = RegistrationCheck("invalid reg");
        BOOST_CHECK(!check.getResponse());
    }

BOOST_AUTO_TEST_SUITE_END()