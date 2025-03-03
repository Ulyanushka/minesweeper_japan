#ifndef FIELD_DATA_H
#define FIELD_DATA_H

#include <QSet>


enum class CellType {
    Void,
    Counter,
    Mine
};


class CellData {
public:
    CellData() = default;
    ~CellData() = default;

    QString GetText() const;
    CellType GetType() const;

    void IncreaseCounter();
    void SetMine();

private:
    CellType type = CellType::Void;
    int near_mines_counter = 0;
};


class FieldData
{
public:
    FieldData(int rows, int cols, int mines);
    ~FieldData() = default;

    CellData& GetCellData(int id);
    QList<int> GetNeighbours(int id);

private:
    QSet<int> GetMinesPlaces();
    void SetMinesAndCounters(QSet<int>& mines_cells);

private:
    int rows;
    int cols;
    int mines_number;
    int cells_number;

    QList<CellData> cells;
};

#endif // FIELD_DATA_H
