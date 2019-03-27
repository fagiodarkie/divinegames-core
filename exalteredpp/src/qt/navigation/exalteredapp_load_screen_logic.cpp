#include "exalteredapp.h"

#include <QGridLayout>
#include <QMenuBar>
#include <screen/qmainscreen.h>
#include <screen/qloadcharacterscreen.h>
#include <screen/qcharacterattributes.h>

using namespace qt::screen;

void ExalteredApp::load_character_screen()
{
  character_info_screen_widget = new qcharacterinfoscreen(current_character, character_manager, this);
  setCentralWidget(character_info_screen_widget);
}

void ExalteredApp::load_attributes_screen()
{
  character_attributes_widget = new qcharacterattributes(current_character, this);
  setCentralWidget(character_attributes_widget);
}

void ExalteredApp::load_abilities_screen()
{
  character_abilities_widget = new qcharacterabilities(current_character, this);
  setCentralWidget(character_abilities_widget);
}

void ExalteredApp::load_main_screen(QSharedPointer<character::character> character)
{
  current_character = character;
  main_screen_widget = new qmainscreen(this);
  setCentralWidget(main_screen_widget);
  load_menu();
}

void ExalteredApp::init_load_character_screen()
{
  load_character_screen_widget = new qloadcharacterscreen(character_manager, this);
  setCentralWidget(load_character_screen_widget);

  connect(load_character_screen_widget, &qloadcharacterscreen::character_loaded, this, &ExalteredApp::load_main_screen);
}