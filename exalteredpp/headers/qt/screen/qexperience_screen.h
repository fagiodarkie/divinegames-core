#ifndef QEXPERIENCE_SCREEN_H
#define QEXPERIENCE_SCREEN_H

#include <QWidget>
#include <QPushButton>

#include "character.h"
#include "widget/session_experience_logger.h"
#include "managers/character_manager.h"

namespace qt { namespace screen {

    class qexperience_screen : public QWidget
    {
      Q_OBJECT
    public:
      explicit qexperience_screen(std::shared_ptr<character::character> character,
                                  manager::character_manager &ch_manager,
                                  QWidget *parent = nullptr);


    signals:

    public slots:

    private:
      widget::session_experience_logger *_logger;
      QPushButton *open_logger;

      void recompute_logger_session();

      std::shared_ptr<character::character> _character;
      manager::character_manager _character_manager;
    };

} }

#endif // QEXPERIENCE_SCREEN_H