#include "field_view.h"

#include <QGridLayout>


inline static const char* closed_cell_color = "background-color: rgba(46, 204, 113, 0.4);";
inline static const char* marked_cell_color = "background-color: rgba(46, 204, 113, 0.8);";

inline static const char* mine_cell_color = "background-color: rgba(185, 29, 113, 0.4);";
inline static const char* counter_cell_color = "background-color: rgba(222, 246, 21, 0.4);";
inline static const char* void_cell_color = "background-color: rgba(0,0,0,0);";


CellView::CellView(int id, CellData* data, QWidget* parent)
    : QPushButton(parent), id(id), data(data)
{
    setFixedSize(20, 20);
    setStyleSheet(closed_cell_color);
}

CellView::~CellView()
{
    data = nullptr;
}

void CellView::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) Open();
    else if (e->button() == Qt::RightButton) Mark();
}

bool CellView::IsOpened()
{
    return is_opened;
}

void CellView::Open()
{
    if (is_opened) return;

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

void CellView::Mark()
{
    if (is_opened) return;
    (is_marked) ? setStyleSheet(closed_cell_color) : setStyleSheet(marked_cell_color);
    is_marked = !is_marked;
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
    cells.push_back(new CellView(id, &data->GetCellData(id)));
    connect(cells[id], &CellView::VoidOpened, this, &FieldView::OpenVoidArea);
    connect(cells[id], &CellView::MineOpened, this, &FieldView::Boom);
}

void FieldView::OpenVoidArea(int id)
{
    QList<int> neighbours = data->GetNeighbours(id);
    for (const auto& n : neighbours) {
        cells[n]->Open();
    }
}

void FieldView::Boom(int id)
{

}
