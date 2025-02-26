#include "field_data.h"

#include <QRandomGenerator>


FieldData::FieldData(int rows, int cols, int mines)
    : rows(rows), cols(cols), mines_number(mines), cells(cells_number), cells_number(rows*cols)
{
    QSet<int> mines_cells = GetMinesPlaces();
    SetMinesAndCounters(mines_cells);
}

QString FieldData::GetCellData(int i)
{
    if (i < 0 || i >= cells_number) return QString();

    if (cells[i].is_mine == true) return QString("M");
    if (cells[i].near_mines_counter == 0) return QString();
    return QString::number(cells[i].near_mines_counter);
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
        cells[m].is_mine = true;

        bool not_very_left = (m % cols != 0);
        bool not_very_right = (m % cols != cols-1);

        if (not_very_left) cells[m-1].near_mines_counter++; //left
        if (not_very_right) cells[m+1].near_mines_counter++; //right

        if (m >= cols) { //not very top
            cells[m-cols].near_mines_counter++; //top
            if (not_very_left) cells[m-cols-1].near_mines_counter++; //left top
            if (not_very_right) cells[m-cols+1].near_mines_counter++; //right top
        }

        if (m < cols*(rows-1)) { //not very bottom
            cells[m+cols].near_mines_counter++; //bottom
            if (not_very_left) cells[m+cols-1].near_mines_counter++; //left bottom
            if (not_very_right) cells[m+cols+1].near_mines_counter++; //right bottom
        }
    }
}
