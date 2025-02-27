#include "field_view.h"

#include <QGridLayout>


inline static const char* normal_cell_color = "background-color: rgba(46, 204, 113, 0.4);";
inline static const char* marked_cell_color = "background-color: rgba(46, 204, 113, 0.8);";

inline static const char* mine_cell_color = "background-color: rgba(185, 29, 113, 0.4);";
inline static const char* counter_cell_color = "background-color: rgba(222, 246, 21, 0.4);";
inline static const char* void_cell_color = "background-color: rgba(0,0,0,0);";


CellView::CellView(int id, const QString& data, QWidget* parent)
    : QPushButton(parent), id(id), text(data)
{
    is_void = (text.isEmpty());
    is_mine = (text == "M");

    setFixedSize(20, 20);
    setStyleSheet(normal_cell_color);
}

void CellView::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) Open();
    else if (e->button() == Qt::RightButton) Mark();
}

void CellView::Open()
{
    is_opened = true;
    setText(text);

    if (is_mine) {
        setStyleSheet(mine_cell_color);
        emit MineOpened(id);
    }
    else if (is_void) {
        setStyleSheet(void_cell_color);
        emit VoidOpened(id);
    }
    else {
        setStyleSheet(counter_cell_color);
    }
}

void CellView::Mark()
{
    if (!is_opened) setStyleSheet(marked_cell_color);
}


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

    for (int i = 0; i < rows * cols; i++) {
        MakeCell(i);
        grid_lay->addWidget(cells[i], i / cols, i % cols);
    }

    setLayout(grid_lay);
}

void FieldView::MakeCell(int id)
{
    cells.push_back(new CellView(id, data->GetCellData(id)));
    connect(cells[id], &CellView::VoidOpened, this, &FieldView::OpenVoidArea);
    connect(cells[id], &CellView::MineOpened, this, &FieldView::Boom);
}

void FieldView::OpenVoidArea(int id)
{

}

void FieldView::Boom(int id)
{

}
