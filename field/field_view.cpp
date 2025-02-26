#include "field_view.h"

#include <QGridLayout>


const QString normal_btn_color = "background-color: rgba(46, 204, 113, 0.4);";
const QString clicked_btn_color = "background-color: rgba(0,0,0,0);";


FieldView::FieldView(int rows, int cols, int mines, QWidget* parent) : QWidget(parent)
{
    data = new FieldData(rows, cols, mines);
    MakeField(rows, cols);
}

FieldView::~FieldView()
{
    if (data != nullptr) delete data;
    data = nullptr;
}

void FieldView::MakeField(int rows, int cols)
{
    QGridLayout* grid_lay = new QGridLayout(this);
    grid_lay->setHorizontalSpacing(0);
    grid_lay->setVerticalSpacing(0);

    cells = QList<QPushButton*>(rows*cols);
    for (int i = 0; i < rows * cols; i++) {
        cells[i] = new QPushButton();
        connect(cells[i], &QPushButton::clicked, this, [=](){ UncoverCell(i); });

        cells[i]->setFixedSize(20, 20);
        cells[i]->setStyleSheet(normal_btn_color);
        grid_lay->addWidget(cells[i], i / cols, i % cols);
    }

    setLayout(grid_lay);
}

void FieldView::UncoverCell(int i)
{
    cells[i]->setText(data->GetCellData(i));
    cells[i]->setStyleSheet(clicked_btn_color);
}
