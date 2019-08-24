#pragma once

#include "common_worker.h"

namespace calculator {
  namespace worker {

    class exalt_worker : public common_worker<round_up>
    {
    public:
      ~exalt_worker() override;

      virtual long int compute_persona(const character::creation::character_type& type, const character::attributes& attributes, const character::power::willpower& willpower, const character::power::essence& essence) const override;

    protected:
      virtual double _natural_aggravated_soak(const character::character& c) const override;
    };

  }
}