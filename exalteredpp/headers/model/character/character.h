#pragma once

#include <string>
#include "../thirdparty/serialisable/serialisable.hpp"
#include <social/persona.h>
#include "character/attributes/attributes.h"
#include "character/abilities/abilities.h"
#include "creation/character_type_model.h"
#include "exalt/exalt_caste.h"
#include "virtues/virtues.h"
#include "power/power_container.h"

namespace character
{
  class character : public Serialisable
  {
    public:
      // constructors
      character(const QString name,
                const creation::character_type type,
                const exalt::caste caste,
                const attributes attributes,
                const abilities abilities,
                const virtues::virtues virtues,
                const power::power_container power_container,
                const unsigned int id = 0);
      character(const character& other);

      // character fields
      std::string get_name() const;
      void set_name(const std::string& new_name);

      creation::character_type get_type() const;
      void set_type(creation::character_type type);

      attribute get_attribute(attribute_names::attribute name) const;
      void set_attribute(attribute_names::attribute name, attribute attribute);

      ability_group get_ability_group(ability_names::ability_enum name) const;
      ability get_ability(ability_names::ability_enum name, const std::string& ability_declination = ability_names::ability_declination::NO_DECLINATION) const;
      void set_ability(ability_names::ability_enum name, ability_group ability);

      unsigned int id() const;
      exalt::caste caste() const;

      virtual void serialisation() override;
      virtual ~character();

    private:
      std::string                   _name;
      creation::character_type  _type;
      unsigned int              _id;

      exalt::caste              _character_caste;
      attributes                _attributes;
      abilities                 _abilities;
      virtues::virtues          _virtues;
      power::power_container    _power;
      social::persona           _persona;

    };
}
