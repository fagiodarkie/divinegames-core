#pragma once
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QWidget>

#include "attributes/attributes.h"
#include "attributes/attribute_names.h"

namespace qt {
  namespace wizard {

    class character_creation_attribute_points_page : public QWidget
    {
      Q_OBJECT

    public:
      explicit character_creation_attribute_points_page(QWidget *parent = nullptr);

      void set_total_points(QMap<character::attribute_names::attribute_category, unsigned int> points_per_category);

    signals:
      void back_issued();
      void attribute_points_chosen(const character::attributes& chosen_attributes);
      void total_changed(character::attribute_names::attribute_category category);

    private slots:
      void increase_attribute();
      void decrease_attribute();


    private:
      character::attributes chosen_attributes;

      QMap<character::attribute_names::attribute_category, unsigned int> points_per_category;

      QMap<character::attribute_names::attribute_category, QGroupBox*> group_label_by_category;
      QMap<character::attribute_names::attribute_category, QList<QPushButton*>> increase_buttons_by_category, decrease_buttons_by_category;

      QMap<character::attribute_names::attribute, QLabel*> label_by_attribute;
      QMap<character::attribute_names::attribute, QPushButton*> increase_buttons_by_attribute, decrease_buttons_by_attribute;

      unsigned int total_points_for_category(character::attribute_names::attribute_category att_category);
      unsigned int max_points_for_category(character::attribute_names::attribute_category att_category);

      QPushButton* generate_add_button();
      QPushButton* generate_subtract_button();
      QPushButton *next_page, *cancel;

      void chose_points();
      void generate_group_labels();
      void generate_attribute_labels();
      void generate_attribute_labels_for_category(character::attribute_names::attribute_category category);
      character::attribute_names::attribute retrieve_attribute_from_call();

      void rethink_button_enable(character::attribute_names::attribute_category category);

      QWidget* generate_category_group(character::attribute_names::attribute_category category);
      QWidget* generate_plusminus_buttons_widget(QPushButton* add, QPushButton* subtract);
    };
  }
}