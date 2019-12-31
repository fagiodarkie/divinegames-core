#include "screen/qexperience_screen.h"
#include "layout/qborderlayout.h"

namespace qt { namespace screen {

qexperience_screen::qexperience_screen(std::shared_ptr<character::character> character,
                                       manager::character_manager &ch_manager,
                                       QWidget *parent) : QWidget(parent), _character(character), _character_manager(ch_manager)
{
  open_logger = new QPushButton("Add session");

  _logger = new widget::session_experience_logger;

  connect(open_logger, &QPushButton::clicked, _logger, &QDialog::show);

  layout::QBorderLayout *outer = new layout::QBorderLayout;

  outer->addWidget(open_logger, layout::QBorderLayout::South);

  recompute_logger_session();
  setLayout(outer);
}

void qexperience_screen::recompute_logger_session()
{
  _logger->set_next_session_number(_character->get_experience().last_session() + 1);
}


} }