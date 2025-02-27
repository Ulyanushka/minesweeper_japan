#include "field_data.h"

#include <QRandomGenerator>


QString CellData::GetText() const
{
    switch (type) {
        case CellType::Mine:    return "M";
        case CellType::Counter: return QString::number(near_mines_counter);
        case CellType::Void:
        default:                return QString();
    };
}

CellType CellData::GetType() const
{
    return type;
}

void CellData::IncreaseCounter()
{
    if (near_mines_counter == 0 || type != CellType::Mine) type = CellType::Counter;
    near_mines_counter++;
}

void CellData::SetMine()
{
    type = CellType::Mine;
}


FieldData::FieldData(int rows, int cols, int mines)
    : rows(rows), cols(cols), mines_number(mines), cells(cells_number), cells_number(rows*cols)
{
    QSet<int> mines_cells = GetMinesPlaces();
    SetMinesAndCounters(mines_cells);
}

CellData& FieldData::GetCellData(int id)
{
    return cells[id];
}

QSet<int> FieldData::GetMinesPlaces()
{
    QSet<int> mines_cells;
    while (mines_cells.size() < mines_number) {
        mines_cells.insert(QRandomGenerator::global()->bounded(cells_number));
    }
    return mines_cells;
}

void FieldData::SetMinesAndCounters(QSet<int>& mines_cells)
{
    for (const auto& m : mines_cells) {
        cells[m].SetMine();

        bool not_very_left = (m % cols != 0);
        bool not_very_right = (m % cols != cols-1);

        if (not_very_left) cells[m-1].IncreaseCounter(); //left
        if (not_very_right) cells[m+1].IncreaseCounter(); //right

        if (m >= cols) { //not very top
            cells[m-cols].IncreaseCounter(); //top
            if (not_very_left) cells[m-cols-1].IncreaseCounter(); //left top
            if (not_very_right) cells[m-cols+1].IncreaseCounter(); //right top
        }

        if (m < cols*(rows-1)) { //not very bottom
            cells[m+cols].IncreaseCounter(); //bottom
            if (not_very_left) cells[m+cols-1].IncreaseCounter(); //left bottom
            if (not_very_right) cells[m+cols+1].IncreaseCounter(); //right bottom
        }
    }
}
