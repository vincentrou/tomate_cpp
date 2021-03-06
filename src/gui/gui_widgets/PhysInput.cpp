
#include "PhysInput.h"

#include <QValidator>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>


PhysInput::PhysInput(Rectangle rect, bool editable, QWidget* parent):
    QWidget(parent)
{
    this->setLayout(new QHBoxLayout);

    x_widget = new QLineEdit();
    x_widget->setValidator( new QIntValidator(-10000, 10000, this) );
    y_widget = new QLineEdit();
    y_widget->setValidator( new QIntValidator(-10000, 10000, this) );
    width_widget = new QLineEdit();
    width_widget->setValidator( new QIntValidator(1, 10000, this) );
    height_widget = new QLineEdit();
    height_widget->setValidator( new QIntValidator(1, 10000, this) );
    x_widget->setEnabled(editable);
    y_widget->setEnabled(editable);
    width_widget->setEnabled(editable);
    height_widget->setEnabled(editable);
    this->layout()->addWidget(new QLabel(tr("x position:")));
    this->layout()->addWidget(x_widget);
    this->layout()->addWidget(new QLabel(tr("y position:")));
    this->layout()->addWidget(y_widget);
    this->layout()->addWidget(new QLabel(tr("width:")));
    this->layout()->addWidget(width_widget);
    this->layout()->addWidget(new QLabel(tr("height:")));
    this->layout()->addWidget(height_widget);

    if (rect)
    {
        set_rect(rect);
    }
}

Rectangle PhysInput::get_rect()
{
    int posx = x_widget->text().toInt();
    int posy = y_widget->text().toInt();
    int width = width_widget->text().toInt();
    int height = height_widget->text().toInt();
    return Rectangle(width, height, posx, posy);
}

void PhysInput::set_rect(Rectangle rect)
{
    x_widget->setText(QString::number(rect.get_x()));
    y_widget->setText(QString::number(rect.get_y()));
    width_widget->setText(QString::number(rect.get_width()));
    height_widget->setText(QString::number(rect.get_height()));
}


SubdWidget::SubdWidget(QWidget *parent, QVector<Rectangle> all_rects):
    QWidget(parent)
{
    QGroupBox* group_box = new QGroupBox(tr("subdivisions"));
    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(group_box);

    group_box->setMinimumHeight(250);

    main_layout = new QVBoxLayout();

    QWidget* main_w = new QWidget();
    group_box->setLayout(new QVBoxLayout());
    QScrollArea* scroll_area = new QScrollArea();
    scroll_area->setWidgetResizable(true);
    scroll_area->setWidget(main_w);
    group_box->layout()->addWidget(scroll_area);
    main_w->setLayout(main_layout);

    this->set_rects(all_rects);
}

void SubdWidget::set_rects(QVector<Rectangle> all_rects)
{
    clear();

    for (Rectangle rect: all_rects)
    {
        PhysInput* input = new PhysInput(rect, false);
        inputs.push_back(input);
        this->main_layout->addWidget(input);
    }
}

void SubdWidget::clear()
{
    for (PhysInput* widget: inputs)
    {
        this->main_layout->removeWidget(widget);
        delete widget;
    }
    inputs.clear();
}
