#include "invalid_parameter.h"

#include "error_codes.h"

namespace exception {

  const char* invalid_parameter::what() const noexcept (true)
  {
    return error_code::runtime::INVALID_PARAMETER;
  }

}
