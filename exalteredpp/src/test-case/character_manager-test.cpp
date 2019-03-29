#include "../thirdparty/catch/catch.hpp"

#include "errors/characternotfoundexception.h"
#include "managers/character_manager.h"
#include "character_manager_mock.h"

#define CHAR_MAN_TEST_CHAR_NAME "CHARACTER_NAME"


TEST_CASE("character_manager")
{
  QSharedPointer<character_manager_tests::mock_db_abstraction> mock = QSharedPointer<character_manager_tests::mock_db_abstraction>(new character_manager_tests::mock_db_abstraction());

  SECTION("should load character when it is present")
  {
    mock->mock_has_character(true);
    manager::character_manager sut = manager::character_manager(mock);
    QSharedPointer<character::character> result = sut.load_character();
    REQUIRE(result->get_name() == CHAR_MAN_TEST_CHAR_NAME);
  }

  SECTION("should load character when it is not present")
  {
    mock->mock_has_character(false);
    manager::character_manager sut = manager::character_manager(mock);
    QSharedPointer<character::character> result = sut.load_character();
    REQUIRE(result->get_name() != CHAR_MAN_TEST_CHAR_NAME);
  }

  SECTION("should save character without errors")
  {
    manager::character_manager sut = manager::character_manager(mock);
    try
    {
      QSharedPointer<character::character> to_save = QSharedPointer<character::character>(new character::character(CHAR_MAN_TEST_CHAR_NAME));
      sut.save_character(to_save);
      QSharedPointer<character::character> loaded = sut.load_character();
      REQUIRE(to_save->get_name() == loaded->get_name());
    }
    catch(...)
    {
      FAIL("Something went wrong while retrieving saved character");
    }
  }
}
