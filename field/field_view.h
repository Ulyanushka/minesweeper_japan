#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include "field_data.h"

#include <QPushButton>


class FieldView: public QWidget
{
    Q_OBJECT
public:
    FieldView(int rows, int cols, int mines, QWidget* parent = nullptr);
    ~FieldView();

private:
    void MakeField(int rows, int cols);
    void UncoverCell(int cell);

private:
    QList<QPushButton*> cells;
    FieldData* data;
};

#endif // FIELDVIEW_H
