#include "widget/experience_purchase_widget.h"

#include "narrative/experience_defines.h"
#include "attributes/attribute_names.h"
#include "virtues/virtue_names.h"

#include "layout/qborderlayout.h"
#include <QVBoxLayout>

namespace qt { namespace widget {

    using namespace character::narrative;
    using namespace character;

    experience_purchase_widget::experience_purchase_widget(QWidget* parent) : QDialog(parent)
    {
      setWindowTitle("Purchase");

      attribute_dropdown = new QComboBox;
      virtue_dropdown = new QComboBox;
      purchase_type_dropdown = new QComboBox;
      ability_selector = new widget::ability_declination_selector(ability_names::WAR, true, true, false);
      specialty_freetext = new QLineEdit;
      cost_label = new QLabel("Total cost: gnegne");
      purchase_submit = new QPushButton("Purchase!");

      for (auto purchase_type: EXPENSE_TYPES)
        purchase_type_dropdown->addItem(EXPENSE_NAME.at(purchase_type).c_str(), purchase_type);

      for (auto attribute: attribute_names::ATTRIBUTES)
        attribute_dropdown->addItem(attribute_names::ATTRIBUTE_NAME.at(attribute).c_str(), attribute);

      for (auto virtue: virtues::VIRTUE_LIST)
        virtue_dropdown->addItem(virtues::VIRTUE_NAME.at(virtue).c_str(), virtue);

      connect(purchase_type_dropdown, &QComboBox::currentTextChanged, this, &experience_purchase_widget::purchase_type_selected);

      purchase_type_selected();
    }

    int experience_purchase_widget::selected_purchase_type() const
    {
      return purchase_type_dropdown->currentData().toInt();
    }

    void experience_purchase_widget::purchase_type_selected()
    {
      auto purchase_type = selected_purchase_type();

      // attribute_dropdown->hide();
      // virtue_dropdown->hide();
      // ability_selector->hide();
      // specialty_freetext->hide();

      QList<QWidget*> widgets_in_list;

      switch (purchase_type)
        {
        case ATTRIBUTE:
          {
            widgets_in_list = { attribute_dropdown };
            break;
          }
        case SPECIALISATION:
          {
            widgets_in_list = { ability_selector, specialty_freetext };
            break;
          }
        case ABILITY:
          {
            widgets_in_list = { ability_selector };
            break;
          }
        case VIRTUE:
          {
            widgets_in_list = { virtue_dropdown };
            break;
          }
        default: { }
        }

      compute_cost();
      redraw(widgets_in_list);
    }

    void experience_purchase_widget::redraw(const QList<QWidget*> widgets_in_list)
    {
      delete layout();

      QVBoxLayout *list = new QVBoxLayout;
      list->addWidget(purchase_type_dropdown);

      for (auto widget: widgets_in_list)
        list->addWidget(widget);

      list->addWidget(cost_label);
      list->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
      QWidget *list_widget = new QWidget;
      list_widget->setLayout(list);
      list_widget->adjustSize();

      QVBoxLayout *buttons = new QVBoxLayout;
      buttons->addWidget(purchase_submit);
      QWidget *buttons_widget = new QWidget;
      buttons_widget->setLayout(buttons);

      layout::QBorderLayout *outer = new layout::QBorderLayout;
      outer->addWidget(buttons_widget, layout::QBorderLayout::South);
      outer->addWidget(list_widget, layout::QBorderLayout::Center);
      setLayout(outer);
    }

    void experience_purchase_widget::compute_cost() const
    {
      // TODO
    }

    void experience_purchase_widget::compute_purchase() const
    {
      // TODO
    }

} }
