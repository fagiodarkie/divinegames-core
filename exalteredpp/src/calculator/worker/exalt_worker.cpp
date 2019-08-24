#include "calculator/worker/exalt_worker.h"
#include <algorithm>

namespace calculator {
  namespace worker {

    exalt_worker::~exalt_worker() {}

    long int exalt_worker::compute_persona(const character::creation::character_type& type, const character::attributes& attributes, const character::power::willpower& willpower, const character::power::essence& essence) const
    {
      std::vector<unsigned int> all_values;
      all_values.push_back(willpower.permanent_willpower());
      all_values.push_back(essence.permanent_essence());

      for (auto social_attribute : character::attribute_names::ATTRIBUTES_BY_CATEGORY.at(character::attribute_names::SOCIAL))
        all_values.push_back(attributes.at(social_attribute));

      std::sort(all_values.begin(), all_values.end());

      unsigned int result = 0;
      // start from 0 - drop lowest
      for (int i = 1; i < all_values.size(); ++i)
        {
          result += all_values[i];
        }

      return result;
    }

    double exalt_worker::_natural_aggravated_soak(const character::character& c) const
    {
      return c.get_attribute(attribute_t::CONSTITUTION) / 4;
    }

  }
}