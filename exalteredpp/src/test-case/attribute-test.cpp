#include "../thirdparty/catch/catch.hpp"
#include "attributes/attribute.h"

#define TEST_ATTRIBUTE_NAME "test-attribute"
#define TEST_ATTRIBUTE_VALUE 1

TEST_CASE("Attribute")
{
  SECTION("should create new attribute correctly (name constructor)")
  {
    character::attribute sut(TEST_ATTRIBUTE_NAME);
    REQUIRE(QString(TEST_ATTRIBUTE_NAME) == QString(sut));
    REQUIRE(0 == int(sut));
  }

  SECTION("should create new attribute correctly (name and value constructor)")
  {
    character::attribute sut(TEST_ATTRIBUTE_NAME, TEST_ATTRIBUTE_VALUE);
    REQUIRE(QString(TEST_ATTRIBUTE_NAME) == QString(sut));
    REQUIRE(TEST_ATTRIBUTE_VALUE == int(sut));
  }

  SECTION("should retrieve correctly name and value strings")
  {
    character::attribute sut(TEST_ATTRIBUTE_NAME, TEST_ATTRIBUTE_VALUE);
    REQUIRE(sut.get_name() == TEST_ATTRIBUTE_NAME);
    REQUIRE(sut.get_value() == QString::number(TEST_ATTRIBUTE_VALUE));
  }
}
