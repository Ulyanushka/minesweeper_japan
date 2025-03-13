#ifndef STATDATA_H
#define STATDATA_H

#include <QLabel>


class StatData : public QWidget
{
    Q_OBJECT
public:
    StatData(QWidget* parent = nullptr);
    ~StatData() = default;

    void Reset(int mines);
    void UpdateMinesData(int counter);
    void AddMistake();
    void AddClick();

private:
    void UpdateMistakesData();
    void UpdateClicksData();

private:
    QLabel* mines_data;
    int mines_sum;

    QLabel* mistakes_data;
    int mistakes_counter;

    QLabel* clicks_data;
    int clicks_counter;
};

#endif // STATDATA_H
