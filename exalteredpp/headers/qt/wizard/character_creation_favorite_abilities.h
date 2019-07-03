#pragma once

#include <QCheckBox>
#include <QPushButton>
#include <QWidget>

#include "abilities/abilities.h"
#include "abilities/ability_names.h"
#include "exalt/exalt_caste.h"

namespace qt {
  namespace wizard {
    class character_creation_favorite_abilities : public QWidget
    {
      Q_OBJECT
    public:
      character_creation_favorite_abilities(QWidget *parent = nullptr);

      void set_current_abilities(const character::abilities& new_abilities, unsigned int ability_points, unsigned int min_points_in_favored, unsigned int max_std_value);

    signals:
      void back_issued();
      void abilities_selected(QList<character::ability_names::ability_enum> favorite_abilities);

    public slots:

    private:
      QMap<QCheckBox*, character::ability_names::ability_enum> ability_of_button;
      void next_issued();
      void check_current_selection();
      void allow_check_on_non_caste_abilities();

      unsigned int distributed_points() const;

      QPushButton *next_page, *cancel;
      character::abilities _abilities;
      unsigned int max_std, min_in_favored, total_points;
      QList<character::ability_names::ability_enum> abilities_of_caste;
    };
  }
}

