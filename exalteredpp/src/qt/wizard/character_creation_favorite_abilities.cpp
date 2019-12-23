#include "wizard/character_creation_favorite_abilities.h"

#include <QScrollArea>

#include "label/interfacelabels.h"
#include "layout/qborderlayout.h"

namespace qt {
  namespace wizard {

    using namespace qt::labels::creation_wizard;
    using namespace qt::labels;

    character_creation_favorite_abilities::character_creation_favorite_abilities(QWidget *parent)
      : QWidget(parent)
    {

      QWidget* abilities = new QWidget;
      QVBoxLayout *ability_list = new QVBoxLayout;

      QMap<character::ability_names::ability_category, QGroupBox*> ability_groups;
      QMap<character::ability_names::ability_category, QVBoxLayout*> ability_layouts;

      {
        caste_category_group = new QGroupBox(exalt_labels::CASTE_ABILITIES);
        caste_category_group->setLayout(new QVBoxLayout);
        ability_list->addWidget(caste_category_group);
      }

      for (auto ab_category: character::ability_names::ABILITY_CATEGORIES)
        {
          QGroupBox *category_group = new QGroupBox(character::ability_names::ABILITY_CATEGORY_NAMES.at(ab_category).c_str());
          category_group->setLayout(new QVBoxLayout);
          ability_groups[ab_category] = category_group;
          ability_list->addWidget(category_group);
        }

      for (auto ability_enum : character::ability_names::ABILITIES)
        {
          QWidget* ability_widget = generate_widget(ability_enum);
          ability_of_button[ability_widget] = ability_enum;
          ability_groups[character::ability_names::CATEGORY_OF_ABILITY(ability_enum)]->layout()->addWidget(ability_checkbox);
          connect(ability_checkbox, &QCheckBox::clicked, this, &character_creation_favorite_abilities::check_current_selection);
        }

      abilities->setLayout(ability_list);
      QScrollArea *scroll_abilities = new QScrollArea;
      scroll_abilities->setWidget(abilities);

      QHBoxLayout* buttons_layout = new QHBoxLayout;
      next_page = new QPushButton(NEXT_LABEL);
      cancel = new QPushButton(CANCEL_LABEL);
      buttons_layout->addWidget(cancel);
      buttons_layout->addWidget(next_page);

      next_page->setEnabled(false);
      connect(next_page, &QPushButton::clicked, this, &character_creation_favorite_abilities::next_issued);
      connect(cancel, &QPushButton::clicked, this, &character_creation_favorite_abilities::back_issued);

      QWidget* buttons = new QWidget;
      buttons->setLayout(buttons_layout);

      layout::QBorderLayout *outer_layout = new layout::QBorderLayout;
      outer_layout->addWidget(scroll_abilities, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons, layout::QBorderLayout::South);

      setLayout(outer_layout);
    }

    void character_creation_favorite_abilities::set_current_abilities(const character::abilities &new_abilities, character::exalt::caste selected_caste, unsigned int number_of_default_favorites, unsigned int number_of_favorite_abilities)
    {
      _abilities = new_abilities;
      default_favorite = number_of_default_favorites;
      max_favorite = number_of_favorite_abilities;

      auto abilities = character::exalt::exalt_caste::get_caste(selected_caste).abilities();
      abilities_of_caste = QList<character::ability_names::ability_enum>::fromVector(QVector<character::ability_names::ability_enum>::fromStdVector(abilities));

      for (auto checkbox: ability_of_button.keys())
        checkbox->setChecked(false);

      check_current_selection();
    }

    void character_creation_favorite_abilities::allow_check_on_non_caste_abilities()
    {
      for (auto checkbox: ability_of_button.keys())
        {
          bool is_caste_ability = abilities_of_caste.contains(ability_of_button[checkbox]);
          checkbox->setChecked(checkbox->isChecked()
                               || is_caste_ability
                               || _abilities[ability_of_button[checkbox]]
              .get_ability(sub_ability_of_button[checkbox])
              .is_favourite());
          checkbox->setEnabled(!is_caste_ability);
        }
    }

    void character_creation_favorite_abilities::check_current_selection()
    {
      auto selected = selected_abilities();
      for (character::ability_names::ability_enum ability: character::ability_names::ABILITIES)
        {
          _abilities[ability].set_favourite(selected.contains(ability), );
        }

      bool finished_selecting = static_cast<unsigned int>(selected_abilities().size()) == max_favorite + default_favorite;
      if (finished_selecting)
        {
          for (auto checkbox: ability_of_button.keys())
            {
              bool is_caste_ability = abilities_of_caste.contains(ability_of_button[checkbox]);
              checkbox->setEnabled(!is_caste_ability && _abilities[ability_of_button[checkbox]]
                  .get_ability(sub_ability_of_button[checkbox])
                  .is_favourite());
            }

        }
      else
        allow_check_on_non_caste_abilities();

      next_page->setEnabled(finished_selecting);
    }

    void character_creation_favorite_abilities::next_issued()
    {
      emit abilities_selected(selected_abilities());
    }

    QList<character::ability_names::detailed_ability> character_creation_favorite_abilities::selected_abilities() const
    {
      QList<character::ability_names::detailed_ability> selected_favorites;

      for (auto checkbox: ability_of_button.keys())
        {
          if (checkbox->isChecked())
            selected_favorites.push_back(character::ability_names::detailed_ability(ability_of_button[checkbox], sub_ability_of_button[checkbox]));
        }

      return selected_favorites;
    }

    QWidget* character_creation_favorite_abilities::generate_widget(character::ability_names::ability_enum ability)
    {
      if (!character::ability_names::has_declination(ability))
        return new QCheckBox(character::ability_names::ABILITY_NAME.at(ability).c_str());


    }

  }
}
