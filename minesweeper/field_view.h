#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include "field_data.h"

#include <QPushButton>
#include <QMouseEvent>


class CellView : public QPushButton
{
    Q_OBJECT
public:
    CellView(int id, QWidget* parent = nullptr);
    ~CellView();

    void UpdateData(CellData* new_data);
    void Open();
    void Hide();

signals:
    void Clicked();
    void CounterOpened();
    void MineOpened(int id);
    void VoidOpened(int id);
    void Marked();
    void Unmarked();

protected:
    void mousePressEvent(QMouseEvent* e) override;

private:
    void Close();
    void Mark();

private:
    int id;
    bool is_opened;
    bool is_marked;
    CellData* data;
};


class FieldView: public QWidget
{
    Q_OBJECT
public:
    FieldView(int rows, int cols, int mines, QWidget* parent = nullptr);
    ~FieldView();

    void Reset(int new_mines);
    void HideMine();

signals:
    void Clicked();
    void FieldIsCompleted();
    void FieldIsBoomed();
    void MarksCounterChanged(int counter);

private:
    void ResetData();

    void ResetField();
    void MakeCell(int id);

    void CheckIsCompleted();
    void OpenVoidArea(int id_central_cell);
    void Boom(int id_mine);

private:
    int rows, cols, mines;
    int marks_counter = 0;
    int detected_cells_counter = 0;
    int opened_mine = 0;

    QList<CellView*> cells;
    FieldData* data = nullptr;
};

#endif // FIELDVIEW_H
