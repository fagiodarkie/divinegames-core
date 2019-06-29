#pragma once

#include <QString>

namespace serialisation
{
  struct json_constants
  {
    static const QString SLOT_ID;
    static const QString SLOT_NAME;
    static const QString SLOT_VALUE;
    static const QString SLOT_ATTRIBUTES;
    static const QString SLOT_ABILITIES;
    static const QString SLOT_SPECIALISATIONS;
    static const QString SLOT_CASTE;
    static const QString SLOT_FAVOURITE;
    static const QString SLOT_RANK;

    static const QString SLOT_VIRTUES;
    static const QString SLOT_VICE_ID;
    static const QString SLOT_VICE_VALUE;

    static const QString SLOT_WILLPOWER_TOTAL;
    static const QString SLOT_WILLPOWER_TEMP;
    static const QString SLOT_HEALTH_TOTAL;
    static const QString SLOT_HEALTH_TEMP;

    static const QString SLOT_HEALTH;
    static const QString SLOT_ESSENCE;
    static const QString SLOT_WILLPOWER;

    static const QString SLOT_ESSENCE_PERMANENT;
    static const QString SLOT_ESSENCE_PERSONAL_TOTAL;
    static const QString SLOT_ESSENCE_PERSONAL_COMMITTED;
    static const QString SLOT_ESSENCE_PERSONAL_SPENT;
    static const QString SLOT_ESSENCE_PERSONAL_BONUS;
    static const QString SLOT_ESSENCE_PERIPHERAL_TOTAL;
    static const QString SLOT_ESSENCE_PERIPHERAL_COMMITTED;
    static const QString SLOT_ESSENCE_PERIPHERAL_SPENT;
    static const QString SLOT_ESSENCE_PERIPHERAL_BONUS;
    static const QString SLOT_ESSENCE_SPIRITUAL_TOTAL;
    static const QString SLOT_ESSENCE_SPIRITUAL_COMMITTED;
    static const QString SLOT_ESSENCE_SPIRITUAL_SPENT;
    static const QString SLOT_ESSENCE_SPIRITUAL_BONUS;
    static const QString SLOT_ESSENCE_KHAN;
    static const QString SLOT_ESSENCE_CELESTIAL_PORTION;

  };
}
