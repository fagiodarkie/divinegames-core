#pragma once

#include <exception>

namespace exception {
  class character_not_found_exception : public std::exception
  {
  public:
    const char* what() const noexcept (true) override;
  };

}

