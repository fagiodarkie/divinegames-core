#ifndef MATERIAL_H
#define MATERIAL_H

#include "../thirdparty/serialisable/serialisable.hpp"

#include "combat/attack_defines.h"
#include <string>
#include <map>
#include <vector>
#include <string>

namespace equipment {
  namespace craft {

    enum class material_category
    {
      METAL,
      WOOD,
      NON_METAL,
      FIBER,
      LUXURY_MATERIAL,
      WIRE
    };

    const static std::map<material_category, std::string> NAME_OF_MATERIAL_CATEGORY
    {
      { material_category::METAL,           "Metal" },  
      { material_category::WOOD,            "Wood" },  
      { material_category::NON_METAL,       "Non-Metal" },      
      { material_category::FIBER,           "Fiber" },  
      { material_category::LUXURY_MATERIAL, "Luxury material" },            
      { material_category::WIRE,            "Wire" }
    };

    enum class submaterial_category
    {
      COMMON_METAL,
      UNCOMMON_METAL,
      MAGICAL_METAL,
      MAGICAL_NON_METAL,
      UNCOMMON_COMPLEX,
      VEGETAL_FIBER,
      ANIMAL_FIBER,
      CURED_ANIMAL_FIBER,
      FINE_HARD_WOOD,
      STRONG_HARD_WOOD,
      SOFT_WOOD,
      MAGICAL_FIBER
    };

    const static std::map<submaterial_category, std::string> NAME_OF_MATERIAL_SUBCATEGORY
    {
      { submaterial_category::COMMON_METAL,       "Common Metal" },
      { submaterial_category::UNCOMMON_METAL,     "Uncommon Metal" },
      { submaterial_category::MAGICAL_METAL,      "Magical Metal" },
      { submaterial_category::MAGICAL_NON_METAL,  "Magical Non-Metal" },
      { submaterial_category::UNCOMMON_COMPLEX,   "Uncommon Complex" },
      { submaterial_category::VEGETAL_FIBER,      "Vegetal Fiber" },
      { submaterial_category::ANIMAL_FIBER,       "Animal Fiber" },
      { submaterial_category::CURED_ANIMAL_FIBER, "Cured Animal Fiber" },
      { submaterial_category::FINE_HARD_WOOD,     "Fine Hard Wood" },
      { submaterial_category::STRONG_HARD_WOOD,   "Strong Hard Wood" },
      { submaterial_category::SOFT_WOOD,          "Soft Wood" },
      { submaterial_category::MAGICAL_FIBER,      "Magical Fiber" }
    };


    const static std::map<material_category, std::vector<submaterial_category>> SUBCATEGORIES_OF_CATEGORY
    {
      { material_category::METAL, { submaterial_category::COMMON_METAL, submaterial_category::UNCOMMON_METAL, submaterial_category::MAGICAL_METAL } },
      { material_category::WOOD, { submaterial_category::FINE_HARD_WOOD, submaterial_category::STRONG_HARD_WOOD, submaterial_category::SOFT_WOOD } },
      { material_category::NON_METAL, { submaterial_category::MAGICAL_NON_METAL, submaterial_category::UNCOMMON_COMPLEX } },
      { material_category::FIBER, { submaterial_category::VEGETAL_FIBER, submaterial_category::ANIMAL_FIBER, submaterial_category::CURED_ANIMAL_FIBER, submaterial_category::MAGICAL_FIBER } }
    };

    enum class hardness_enum
    {
      SOFT,
      MEDIUM,
      HARD
    };

    const static std::map<hardness_enum, std::string> MATERIAL_HARDNESS_NAME
    {
      { hardness_enum::SOFT, "Soft" },
      { hardness_enum::MEDIUM, "Medium" },
      { hardness_enum::HARD, "Hard" }
    };

    class material : public Serialisable
    {
    public:
      material();

      material_category category() const;
      void set_category(const material_category &category);

      submaterial_category subcategory() const;
      void set_subcategory(const submaterial_category &subcategory);

      hardness_enum hardness() const;
      void set_hardness(const enum hardness_enum &hardness);

      std::string name() const;
      void set_name(const std::string &name);

      unsigned short craft_resistance() const;
      void set_craft_resistance(unsigned short craft_resistance);

      unsigned short cost() const;
      void set_cost(unsigned short cost);

      unsigned short availability() const;
      void set_availability(unsigned short availability);

      unsigned short tenaciousness() const;
      void set_tenaciousness(unsigned short tenaciousness);

      unsigned short break_point() const;
      void set_break_point(unsigned short break_point);

      unsigned short slots_taken() const;
      void set_slots_taken(unsigned short slots_taken);

      unsigned short minimum() const;
      void set_minimum(unsigned short minimum);

      void with_soak(combat::damage_type_enum damage, short int soak);
      short int soak(combat::damage_type_enum damage) const;

      void with_damage_bonus(combat::damage_type_enum damage, short int d_bonus);
      short int damage_bonus(combat::damage_type_enum damage) const;

      bool changes_damage_type() const;
      void set_changes_damage_type(bool changes_damage_type);

      combat::damage_type_enum overridden_damage_type() const;
      void set_overridden_damage_type(const combat::damage_type_enum &overridden_damage_type);

      short defense_bonus() const;
      void set_defense_bonus(short defense_bonus);

      short precision_bonus() const;
      void set_precision_bonus(short precision_bonus);

      short drill_bonus() const;
      void set_drill_bonus(short drill_bonus);

      short im_bonus() const;
      void set_im_bonus(short im_bonus);

      void serialisation() override;

    private:
      material_category _category;
      submaterial_category _subcategory;
      enum hardness_enum _hardness;
      std::string _name;

      unsigned short int _craft_resistance, _cost, _availability, _tenaciousness, _break_point, _slots_taken, _minimum;

      short int _defense_bonus, _precision_bonus, _drill_bonus, _im_bonus;
      std::map<combat::damage_type_enum, short int> _soak, _damage_bonus;

      bool _changes_damage_type;
      combat::damage_type_enum _overridden_damage_type;
    };
  }
}

#endif // MATERIAL_H
