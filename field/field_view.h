#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include "field_data.h"

#include <QPushButton>
#include <QMouseEvent>


class CellView : public QPushButton
{
    Q_OBJECT
public:
    CellView(const QString& data, QWidget* parent = nullptr);
    ~CellView() = default;

protected:
    void mousePressEvent(QMouseEvent* e) override;

private:
    void Uncover();
    void Mark();

private:
    bool is_mine;
    bool is_void;
    QString text;
};


class FieldView: public QWidget
{
    Q_OBJECT
public:
    FieldView(int rows, int cols, int mines, QWidget* parent = nullptr);
    ~FieldView();

private:
    void MakeField(int rows, int cols);

private:
    QList<CellView*> cells;
    FieldData* data;
};

#endif // FIELDVIEW_H
