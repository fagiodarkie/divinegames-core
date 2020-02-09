#include "wizard/phys_attack/attack_declaration_precision_page.h"

#include <QGroupBox>
#include <QScrollArea>

#include "label/interfacelabels.h"

namespace qt {
  namespace wizard {

    using namespace labels::wizards::physical_attack;

    attack_declaration_precision_page::attack_declaration_precision_page(std::shared_ptr<character::character> c, QWidget *parent)
      : QWidget(parent)
    {
      layout::QBorderLayout *outer = new layout::QBorderLayout;

      internal_bonus_spin = new QSpinBox;
      internal_bonus_spin->setMinimum(0);

      external_bonus_spin = new QSpinBox;
      external_bonus_spin->setMinimum(0);

      internal_malus_spin = new QSpinBox;
      internal_malus_spin->setMinimum(0);

      external_malus_spin = new QSpinBox;
      external_malus_spin->setMinimum(0);

      weapon_precision_spin = new QSpinBox;
      weapon_precision_spin->setMinimum(0);

      weapon_damage_spin = new QSpinBox;
      weapon_damage_spin->setMinimum(0);

      weapon_drill_spin = new QSpinBox;
      weapon_drill_spin->setMinimum(0);

      weapon_min_spin = new QSpinBox;
      weapon_min_spin->setMinimum(0);

      weapon_damage_attr_box = new QComboBox;
      for (auto attribute: attribute::ATTRIBUTES)
        weapon_damage_attr_box->addItem(attribute::ATTRIBUTE_NAME.at(attribute).c_str(), static_cast<int>(attribute));

      weapon_precision_attr_box = new QComboBox;
      for (auto attribute: attribute::ATTRIBUTES)
        weapon_precision_attr_box->addItem(attribute::ATTRIBUTE_NAME.at(attribute).c_str(), static_cast<int>(attribute));

      weapon_damage_box = new QComboBox;
      for (auto damagetype: combat::DAMAGES)
        weapon_damage_box->addItem(combat::DAMAGE_NAME.at(damagetype).c_str(), static_cast<int>(damagetype));

      weapon_ability_box = new QComboBox;
      for (auto ability: c->abilities().keys())
        weapon_ability_box->addItem(ability.name().c_str(), ability.serialise().c_str());

      body_target_box = new QComboBox;
      for (auto body: combat::BODY_TARGET_LIST)
        body_target_box->addItem(combat::BODY_TARGET_NAME.at(body).c_str(), static_cast<int>(body));
      body_target_box->setCurrentText(combat::BODY_TARGET_NAME.at(combat::body_target::NO_TARGET).c_str());

      for (auto attribute: combat::ATTACK_ATTRIBUTES)
        {
          auto check = new QCheckBox;
          check->setText(combat::ATTACK_ATTRIBUTE_NAME.at(attribute).c_str());
          check->setProperty("attack_attribute", static_cast<int>(attribute));
          attribute_checkboxes.append(check);
        }

      QFormLayout *weapon_form = new QFormLayout;
      weapon_form->addRow(WEAPON_PRECISION     , weapon_precision_spin);
      weapon_form->addRow(WEAPON_DAMAGE        , weapon_damage_spin);
      weapon_form->addRow(WEAPON_MIN_DAMAGE    , weapon_min_spin);
      weapon_form->addRow(WEAPON_DRILL         , weapon_drill_spin);
      weapon_form->addRow(WEAPON_ABILITY       , weapon_ability_box);
      weapon_form->addRow(WEAPON_PRECISION_ATTR, weapon_precision_attr_box);
      weapon_form->addRow(WEAPON_DAMAGE_ATTR   , weapon_damage_attr_box);
      weapon_form->addRow(WEAPON_DAMAGE_TYPE   , weapon_damage_box);
      QGroupBox *weapon_group = new QGroupBox(WEAPON_STATS_TITLE);
      weapon_group->setLayout(weapon_form);

      QFormLayout *attack_form = new QFormLayout;
      attack_form->addRow(INTERNAL_PRECISION_BONUS, internal_bonus_spin);
      attack_form->addRow(INTERNAL_PRECISION_MALUS, internal_malus_spin);
      attack_form->addRow(EXTERNAL_PRECISION_BONUS, external_bonus_spin);
      attack_form->addRow(EXTERNAL_PRECISION_MALUS, external_malus_spin);
      attack_form->addRow(BODY_TARGET, body_target_box);
      for (auto checkbox: attribute_checkboxes)
        attack_form->addRow(checkbox);
      QGroupBox *attack_group = new QGroupBox(ATTACK_STATS_TITLE);
      attack_group->setLayout(attack_form);

      QVBoxLayout *center = new QVBoxLayout;
      center->addWidget(weapon_group);
      center->addWidget(attack_group);
      QWidget* center_widget = new QWidget;
      center_widget->setLayout(center);
      QScrollArea *scroll = new QScrollArea;
      scroll->setWidget(center_widget);

      outer->addWidget(_progress_bar,     layout::QBorderLayout::North);
      outer->addWidget(scroll,            layout::QBorderLayout::Center);
      outer->addWidget(buttons_layout(),  layout::QBorderLayout::South);
      setLayout(outer);

      enable_next();
      on_next_issued([this]() { collect_weapon_and_attributes(); });
    }

    void attack_declaration_precision_page::collect_weapon_and_attributes()
    {
      equip::weapon created_weapon;
      ability::ability_name weapon_ability(ability::ability_enum::WAR);
      weapon_ability.deserialise(weapon_ability_box->currentData().toString().toStdString());
      created_weapon.with_precision(weapon_precision_spin->value())
          .with_base_damage(weapon_damage_spin->value())
          .with_min_damage(weapon_min_spin->value())
          .with_drill(weapon_drill_spin->value())
          .use_with(weapon_ability)
          .requires_for_precision(static_cast<attribute::attribute_enum>(weapon_precision_attr_box->currentData().toInt()))
          .uses_for_damage(static_cast<attribute::attribute_enum>(weapon_damage_attr_box->currentData().toInt()))
          .with_damage_type(static_cast<combat::damage_type_enum>(weapon_damage_box->currentData().toInt()));

      std::vector<combat::attack_attribute> attack_attributes;
      for (auto attack_check: attribute_checkboxes)
        if (attack_check->isChecked())
          attack_attributes.push_back(static_cast<combat::attack_attribute>(attack_check->property("attack_attribute").toInt()));

      emit attack_selected(created_weapon, attack_attributes,
                           internal_bonus_spin->value(), internal_malus_spin->value(),
                           external_bonus_spin->value(), external_malus_spin->value(),
                           static_cast<combat::body_target>(body_target_box->currentData().toInt()));
    }

  }
}