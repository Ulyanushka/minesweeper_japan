#ifndef FIELD_DATA_H
#define FIELD_DATA_H

#include <QSet>


struct Cell {
    Cell() = default;
    bool is_mine = false;
    int near_mines_counter = 0;
};


class FieldData
{
public:
    FieldData(int rows, int cols, int mines); //16,16,40
    ~FieldData() = default;

    QString GetCellData(int i);

private:
    QSet<int> GetMinesPlaces();
    void SetMinesAndCounters(QSet<int>& mines_cells);

private:
    int rows;
    int cols;
    int mines_number;
    int cells_number;

    QList<Cell> cells;
};

#endif // FIELD_DATA_H
