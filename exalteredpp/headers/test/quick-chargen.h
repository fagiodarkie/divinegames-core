#pragma once

#include "character.h"
#include <memory>

std::shared_ptr<character::character> generate_character_pointer(const std::string& name, int id);

character::character generate_character(const std::string& name, int id);
