#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include "field_data.h"

#include <QPushButton>
#include <QMouseEvent>


class CellView : public QPushButton
{
    Q_OBJECT
public:
    CellView(int id, CellData* data, QWidget* parent = nullptr);
    ~CellView();

signals:
    void MineOpened(int id);
    void VoidOpened(int id);

protected:
    void mousePressEvent(QMouseEvent* e) override;

private:
    void Open();
    void Mark();

private:
    int id;
    bool is_opened = false;
    CellData* data;
};


class FieldView: public QWidget
{
    Q_OBJECT
public:
    FieldView(int rows, int cols, int mines, QWidget* parent = nullptr);
    ~FieldView();

private:
    void MakeField(int rows, int cols);
    void MakeCell(int id);

    void OpenVoidArea(int id);
    void Boom(int id);

private:
    QList<CellView*> cells;
    FieldData* data;
};

#endif // FIELDVIEW_H
