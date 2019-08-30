#include "screen/qwillpower_virtues_screen.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QScrollArea>
#include <QString>
#include "layout/qborderlayout.h"
#include "label/interfacelabels.h"

namespace qt {
  namespace screen {

    using namespace labels::will_virtue_labels;
    using namespace labels;
    using namespace character::virtues;

    qwillpower_virtues_screen::qwillpower_virtues_screen(const std::shared_ptr<character::character> c,
                                                   QWidget *parent)
      : QWidget(parent)
    {

      QWidget *wp_widget = new QWidget, *ext_widget = new QWidget;
      //essence_form->addRow(PERSONAL_ESSENCE,    new QLabel(labels::AVAILABLE_OVER_TOTAL(essence.available_personal_essence(), essence.total_personal_essence())));

      QHBoxLayout *wp_layout = new QHBoxLayout;
      wp_layout->addWidget(new QLabel(WILLPOWER));
      wp_layout->addWidget(new QLabel(AVAILABLE_OVER_TOTAL(c->get_willpower().temporary_willpower(), c->get_willpower().permanent_willpower())));
      wp_widget->setLayout(wp_layout);

      QGroupBox *virt_form_widget = new QGroupBox(VIRTUES_SECTION);
      QFormLayout* virt_form = new QFormLayout;
      QVBoxLayout *v_layout = new QVBoxLayout;

      for (auto virtue: VIRTUE_LIST)
        {
          virt_form->addRow(VIRTUE_NAME.at(virtue).c_str(), new QLabel(QString::number(c->get_virtue(virtue).value())));
        }

      QString vice_label = SPECIFY_SUBLABEL(labels::creation_wizard::VICE_SELECTOR, VICE_NAME.at(c->get_vice()).c_str());
      virt_form->addRow(vice_label, new QLabel(QString::number(c->get_vice_value())));
      virt_form_widget->setLayout(virt_form);

      layout::QBorderLayout *external_layout = new layout::QBorderLayout;
      external_layout->addWidget(virt_form_widget, layout::QBorderLayout::Center);
      external_layout->addWidget(wp_widget, layout::QBorderLayout::North);

      ext_widget->setLayout(external_layout);
      QScrollArea *scroll_area = new QScrollArea;
      scroll_area->setWidgetResizable(true);
      scroll_area->setWidget(ext_widget);

      v_layout->addWidget(scroll_area);
      setLayout(v_layout);
    }
  }
}