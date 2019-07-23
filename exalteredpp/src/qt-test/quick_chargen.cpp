#include "qt-test/quick_chargen.h"

std::shared_ptr<character::character> generate_character_pointer(const QString& name, int id)
{
  return std::make_shared<character::character>(name.toStdString(), character::creation::TYPE_MORTAL_HERO, character::exalt::caste::NO_CASTE, character::attributes(), character::abilities(), character::virtues::virtues(), character::power::power_container(), id);
}

character::character generate_character(const QString& name, int id)
{
  return character::character(name.toStdString(), character::creation::TYPE_MORTAL_HERO, character::exalt::caste::NO_CASTE, character::attributes(), character::abilities(), character::virtues::virtues(), character::power::power_container(), id);
}

