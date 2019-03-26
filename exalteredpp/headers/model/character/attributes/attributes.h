#pragma once

#include <map>
#include "attribute_names.h"
#include "attribute.h"
#include "serialisable.h"

namespace character
{
  class attributes : public QMap<attribute_name, attribute>, serialisable
  {

  public:
    void read(const QJsonObject &json) override;
    void write(QJsonObject &json) const override;

    virtual ~attributes() = default;
  };
}

