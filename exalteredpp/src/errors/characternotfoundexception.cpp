#include "characternotfoundexception.h"

#include "error_codes.h"

namespace exception {


  const char* character_not_found_exception::what() const noexcept (true)
  {
    return error_code::serialisation::CHARACTER_NOT_FOUND;
  }
}
