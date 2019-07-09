#include "../thirdparty/catch/catch.hpp"

#include "errors/characternotfoundexception.h"
#include "managers/character_manager.h"
#include "db_abstraction_mock.h"
#include "ability_factory_mock.h"
#include "qt-test/quick_chargen.h"

TEST_CASE("character_manager")
{
  QSharedPointer<mock_tests::mock_db_abstraction> manager_mock = QSharedPointer<mock_tests::mock_db_abstraction>(new mock_tests::mock_db_abstraction());
  QSharedPointer<character::abstract_ability_factory> factory_mock = QSharedPointer<character::abstract_ability_factory>(new mock_tests::mock_ability_factory());

  manager::character_manager sut = manager::character_manager(manager_mock, factory_mock);

  SECTION("should load character when it is present")
  {
    manager_mock->mock_has_character(true);
    QSharedPointer<character::character> result = sut.load_character("name");
    REQUIRE(result->get_name() == CHAR_MAN_TEST_CHAR_NAME);
  }

  SECTION("should save character without errors")
  {
    try
    {
      QSharedPointer<character::character> to_save = generate_character_pointer("name", 0);
      sut.save_character(to_save);
      QSharedPointer<character::character> loaded = sut.load_character("name");
      REQUIRE(to_save->get_name() == loaded->get_name());
    }
    catch(...)
    {
      FAIL("Something went wrong while retrieving saved character");
    }
  }

  SECTION("should create a new character if requested")
  {
    try {
      auto generated = sut.create_character("name", character::creation::TYPE_MORTAL_HERO, character::exalt::caste::NO_CASTE, character::attributes(), character::abilities(), character::virtues::virtues(), character::power::power_container());
      REQUIRE(!generated.isNull());
    }
    catch(...)
    {
      FAIL("Something went wrong while generating character");
    }
  }

  SECTION("should list available characters")
  {
    manager_mock->mock_has_character(true);
    REQUIRE(sut.characters().size() > 0);
  }

  SECTION("will throw if a requested character id doesn't exist")
  {
    manager_mock->mock_has_character(true);
    REQUIRE_THROWS(sut.load_character("non_existing_character_id"));
  }
}
