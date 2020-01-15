#pragma once

#include "behavioral/name_value_pair.h"
#include "../thirdparty/serialisable/serialisable.hpp"

namespace ability
{

  class ability : public Serialisable
  {
  public:
    ability();
    ability(const std::string& name, unsigned int value = 0);
    ability(const ability& o);
    ability& operator=(const ability& o);

    operator unsigned int() const;
    operator std::string() const;
    std::string name() const;

    unsigned int get_ability_value() const;
    bool is_favourite() const;

    void set_value(unsigned int new_value);

    void set_favourite(bool is_favourite);

    virtual void serialisation() override;

    bool operator==(const ability& other) const;

  private:
    std::string _name;
    unsigned int _value;
    bool _favourite;
  };

}
