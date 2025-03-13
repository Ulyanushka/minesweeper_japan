#include "field_data.h"

#include <QRandomGenerator>


//CELL_DATA------------------------------------------------------------------------------


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
    if ((near_mines_counter == 0) && (type != CellType::Mine)) {
        type = CellType::Counter;
    }
    near_mines_counter++;
}

void CellData::SetMine()
{
    type = CellType::Mine;
}


//FIELD_DATA-----------------------------------------------------------------------------


FieldData::FieldData(int rows, int cols, int mines)
    : rows(rows), cols(cols), mines_number(mines),
    cells(cells_number), cells_number(rows*cols)
{
    QList<int> mines_ids = GetMinesPlaces();
    SetMinesAndCounters(mines_ids);
}

CellData& FieldData::GetCellData(int id)
{
    return cells[id];
}

QList<int> FieldData::GetNeighbours(int id)
{
    QList<int> neighbours;

    bool not_very_left = (id % cols != 0);
    bool not_very_right = (id % cols != cols-1);

    if (not_very_left) neighbours.append(id-1); //left
    if (not_very_right) neighbours.append(id+1); //right

    if (id >= cols) { //not very top
        neighbours.append(id-cols); //top
        if (not_very_left) neighbours.append(id-cols-1); //left top
        if (not_very_right) neighbours.append(id-cols+1); //right top
    }

    if (id < cols*(rows-1)) { //not very bottom
        neighbours.append(id+cols); //bottom
        if (not_very_left) neighbours.append(id+cols-1); //left bottom
        if (not_very_right) neighbours.append(id+cols+1); //right bottom
    }

    return neighbours;
}

QList<int> FieldData::GetMinesPlaces()
{
    QList<int> source;
    for (int i = 0; i < cells_number; i++) {
        source.append(i);
    }

    QList<int> mines_ids;
    for (int i = 0; i < mines_number; i++) {
        mines_ids.append(source.takeAt(QRandomGenerator::global()->bounded(source.size())));
    }
    return mines_ids;
}

void FieldData::SetMinesAndCounters(QList<int>& mines_ids)
{
    for (const auto& m : mines_ids) {
        cells[m].SetMine();
        for (const auto& id : GetNeighbours(m)) {
            cells[id].IncreaseCounter();
        }
    }
}
