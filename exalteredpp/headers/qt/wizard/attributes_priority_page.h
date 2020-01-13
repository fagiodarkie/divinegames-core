#pragma once

#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include "attributes/attribute_names.h"
#include "widget/with_progress_bar.h"

namespace qt {
  namespace wizard {

    class attributes_priority_page : public QWidget, public widget::with_progress_bar
    {
      Q_OBJECT

    public:
      attributes_priority_page(QWidget *parent = nullptr);

      ~attributes_priority_page();

      void set_attribute_values(int primary_value, int secondary_value, int tertiary_value);

    signals:
      void attributes_chosen(QString primary_attribute, QString secondary_attribute, QString tertiary_attribute);
      void back_issued();

    private:
      void check_form();
      void chose_all();

      void populate_primary();
      void create_attributes();
      void first_attribute_change();
      void second_attribute_change();
      QString first_attribute_value();
      QString second_attribute_value();

      QComboBox *primary_select, *secondary_select;
      QLabel *third_attribute, *primary_label, *secondary_label, *tertiary_label;
      QPushButton *next_page, *cancel;
      QFormLayout *attributes_form;

      int primary, secondary, tertiary;
    };
  }
}
