#pragma once

#include <exception>

namespace exception {
  class invalid_parameter : public std::exception
  {
  public:
    const char* what() const noexcept (true) override;
  };

}

