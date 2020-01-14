#include "narrative/background_purchase.h"
#include "json_constants.h"

namespace character { namespace narrative {

    background_purchase::background_purchase() : _amount(0) { }

    background_purchase::~background_purchase() { }

    void background_purchase::apply(std::shared_ptr<character>) { }

    void background_purchase::serialisation()
    {
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
    }

    std::string background_purchase::key() const
    {
      return "background";
    }

    std::string background_purchase::description() const
    {
      return key();
    }

}}
