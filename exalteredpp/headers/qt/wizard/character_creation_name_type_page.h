#pragma once

#include <QWizardPage>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>

#include "exalt/exalt_caste.h"
#include "widget/with_progress_bar.h"
#include "creation/character_type_model.h"

namespace qt {
  namespace wizard {

    using character::creation::character_type;

    class character_creation_name_type_page : public QWidget, public widget::with_progress_bar
    {
      Q_OBJECT

    public:
      character_creation_name_type_page(QWidget *parent = nullptr);

    signals:
      void character_type_chosen(const QString& character_name, character_type type, character::exalt::caste caste);
      void back_issued();

    private:
      QLineEdit* character_name;
      QComboBox *combo_box, *caste_combo_box;
      QPushButton *next_page, *cancel;
      QLabel *caste_label;

      void hide_show_caste_box();
      void check_form();
      void chose_all();
    };
  }
}
