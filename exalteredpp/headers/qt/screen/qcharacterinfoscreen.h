#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <character.h>
#include "managers/character_manager.h"

namespace qt
{
  namespace screen
  {
    class qcharacterinfoscreen : public QWidget
    {
        Q_OBJECT
    public:
        explicit qcharacterinfoscreen(QSharedPointer<character::character> character,
                             QSharedPointer<manager::character_manager> ch_manager,
                             QWidget *parent = nullptr);

    signals:

    public slots:

    private:
      void save_character();

      QSharedPointer<character::character> character;
      QSharedPointer<manager::character_manager> character_manager;
      QLineEdit character_name_widget;
      QPushButton save_button;

      void on_text_change(const QString& );
    };

  }
}