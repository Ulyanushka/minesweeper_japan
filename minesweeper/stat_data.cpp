#include "stat_data.h"

#include <QLayout>


StatData::StatData(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* main_lay = new QVBoxLayout();

    mines_data = new QLabel();
    main_lay->addWidget(mines_data);

    mistakes_data = new QLabel();
    main_lay->addWidget(mistakes_data);

    clicks_data = new QLabel();
    main_lay->addWidget(clicks_data);

    setLayout(main_lay);
}

void StatData::Reset(int mines)
{
    mines_sum = mines;
    mistakes_counter = 0;
    clicks_counter = 0;

    UpdateMinesData(0);
    UpdateMistakesData();
    UpdateClicksData();
}

void StatData::UpdateMinesData(int counter)
{
    mines_data->setText(QString("Marks/Mines: %1/%2").arg(counter).arg(mines_sum));
}

void StatData::AddMistake()
{
    mistakes_counter++;
    UpdateMistakesData();
}

void StatData::AddClick()
{
    clicks_counter++;
    UpdateClicksData();
}

void StatData::UpdateMistakesData()
{
    mistakes_data->setText(QString("Mistakes: %1").arg(mistakes_counter));
}

void StatData::UpdateClicksData()
{
    clicks_data->setText(QString("Clicks: %1").arg(clicks_counter));
}
