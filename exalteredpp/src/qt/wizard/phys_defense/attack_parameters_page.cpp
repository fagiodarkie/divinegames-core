#include "wizard/phys_defense/attack_parameters_page.h"

#include "layout/qborderlayout.h"
#include <QFormLayout>
#include <QScrollArea>

namespace qt { namespace wizard {

    attack_parameters_page::attack_parameters_page()
    {
      layout::QBorderLayout *outer = new layout::QBorderLayout;

      precision_result_box = new QSpinBox;
      base_damage_box = new QSpinBox;
      base_damage_box->setMinimum(-15);
      min_damage_box = new QSpinBox;
      drill_box = new QSpinBox;

      damage_type_box = new QComboBox;
      for (auto damage: combat::DAMAGES)
        damage_type_box->addItem(combat::DAMAGE_NAME.at(damage).c_str(), static_cast<int>(damage));

      body_target_box = new QComboBox;
      for (auto target: combat::BODY_TARGET_LIST)
        body_target_box->addItem(combat::BODY_TARGET_NAME.at(target).c_str(), static_cast<int>(target));

      body_target_box->setCurrentText(combat::BODY_TARGET_NAME.at(combat::body_target::NO_TARGET).c_str());

      QFormLayout *vcenter = new QFormLayout;
      vcenter->addWidget(new QLabel("Provide the basic information about the attack."));
      vcenter->addRow("Precision roll result:", precision_result_box);
      vcenter->addRow("Base damage (extra successes excluded):", base_damage_box);
      vcenter->addRow("Weapon damage type:", damage_type_box);
      vcenter->addRow("Minimum damage:", min_damage_box);
      vcenter->addRow("Attack drill:", drill_box);
      vcenter->addRow("Targeted body part:", body_target_box);
      QWidget* center_w = new QWidget;
      center_w->setLayout(vcenter);
      QScrollArea *scroll_w = new QScrollArea;
      scroll_w->setWidget(center_w);

      outer->addWidget(_progress_bar,     layout::QBorderLayout::North);
      outer->addWidget(scroll_w,          layout::QBorderLayout::Center);
      outer->addWidget(buttons_layout(),  layout::QBorderLayout::South);
      setLayout(outer);

      enable_next();
      on_next_issued([this]() {
          auto damage = static_cast<combat::damage_type_enum>(damage_type_box->currentData().toInt());
          auto target = static_cast<combat::body_target>(body_target_box->currentData().toInt());
          emit attack_parameters(target, damage, precision_result_box->value(), base_damage_box->value(), min_damage_box->value(), drill_box->value());
        });
    }
}}
