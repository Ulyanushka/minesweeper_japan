#include "field_view.h"

#include <QGridLayout>


//CELL_VIEW------------------------------------------------------------------------------


inline static const char* closed_cell_color = "background-color: rgba(46, 204, 113, 0.4);";
inline static const char* marked_cell_color = "background-color: rgba(46, 204, 113, 0.8);";

inline static const char* mine_cell_color = "background-color: rgba(185, 29, 113, 0.4);";
inline static const char* counter_cell_color = "background-color: rgba(222, 246, 21, 0.4);";
inline static const char* void_cell_color = "background-color: rgba(0,0,0,0);";


CellView::CellView(int id, QWidget* parent)
    : QPushButton(parent), id(id)
{
    setFixedSize(20, 20);
}

CellView::~CellView()
{
    data = nullptr;
}

void CellView::UpdateData(CellData* new_data)
{
    data = new_data;

    is_opened = false;
    is_marked = false;

    setStyleSheet(closed_cell_color);
    setText("");
}

void CellView::Open()
{
    if (is_opened) return;
    if (is_marked) emit Unmarked();

    is_opened = true;
    setText(data->GetText());

    switch (data->GetType()) {
        case CellType::Mine: {
            setStyleSheet(mine_cell_color);
            emit MineOpened(id);
            break;
        }
        case CellType::Counter: {
            setStyleSheet(counter_cell_color);
            break;
        }
        case CellType::Void: {
            setStyleSheet(void_cell_color);
            emit VoidOpened(id);
            break;
        }
    };
}

void CellView::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        Open();
    }
    else if (e->button() == Qt::RightButton) {
        Mark();
    }
}

void CellView::Mark()
{
    if (is_opened) return;

    if(is_marked) {
        setStyleSheet(closed_cell_color);
        emit Unmarked();
    }
    else {
        setStyleSheet(marked_cell_color);
        emit Marked();
    }

    is_marked = !is_marked;
}


//FIELD_VIEW-----------------------------------------------------------------------------


FieldView::FieldView(int rows, int cols, int mines, QWidget* parent)
    : QWidget(parent), rows(rows), cols(cols), mines(mines)
{
    data = new FieldData(rows, cols, mines);
    MakeField();
    SetData();
}

FieldView::~FieldView()
{
    if (data != nullptr) delete data;
    data = nullptr;
}

void FieldView::Reset()
{
    SetData();
}

void FieldView::SetData()
{
    if (data != nullptr) delete data;
    data = new FieldData(rows, cols, mines);
    for (int i = 0; i < rows * cols; i++) {
        cells[i]->UpdateData(&data->GetCellData(i));
    }
}

void FieldView::MakeField()
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
    cells.push_back(new CellView(id));
    connect(cells[id], &CellView::VoidOpened, this, &FieldView::OpenVoidArea);
    connect(cells[id], &CellView::MineOpened, this, &FieldView::Boom);
    connect(cells[id], &CellView::Marked, this, [this](){ marks_counter++; emit MarksCounterChanged(marks_counter); });
    connect(cells[id], &CellView::Unmarked, this, [this](){ marks_counter--; emit MarksCounterChanged(marks_counter); });
}

void FieldView::OpenVoidArea(int id_central_cell)
{
    QList<int> neighbours = data->GetNeighbours(id_central_cell);
    for (const auto& n : neighbours) {
        cells[n]->Open();
    }
}

void FieldView::Boom(int id_mine)
{
    emit FieldIsBoomed(id_mine);
}
