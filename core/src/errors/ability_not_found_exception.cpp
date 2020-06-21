#include "ability_not_found_exception.h"
#include "error_codes.h"

namespace exception {
  const char* ability_not_found_exception::what() const noexcept (true)
  {
    return error_code::character::ABILITY_NOT_FOUND;
  }
}
