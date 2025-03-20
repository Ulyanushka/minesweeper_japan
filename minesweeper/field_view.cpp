#include "field_view.h"

#include <QLayout>


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

void CellView::SetData(CellData* new_data)
{
    data = new_data;
    Close();
    Unblock();
    setStyleSheet(closed_cell_color);    
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
            emit CounterOpened();
            break;
        }
        case CellType::Void: {
            setStyleSheet(void_cell_color);
            emit VoidOpened(id);
            break;
        }
    };
}

void CellView::Hide()
{
    Close();
    Mark();
}

void CellView::Block()
{
    is_blocked = true;
}

void CellView::Unblock()
{
    is_blocked = false;
}

void CellView::mousePressEvent(QMouseEvent* e)
{
    if (is_blocked || !(e->button() == Qt::LeftButton || e->button() == Qt::RightButton)) return;
    if (!is_opened) emit Clicked();

    if (e->button() == Qt::LeftButton) {
        Open();
    }
    else if (e->button() == Qt::RightButton) {
        Mark();
    }
}

void CellView::Close()
{
    is_opened = false;
    is_marked = false;
    setText("");
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
    ResetField();
    ResetData();
}

FieldView::~FieldView()
{
    if (data != nullptr) delete data;
    data = nullptr;
}

void FieldView::Reset(int new_mines)
{
    mines = new_mines;
    detected_cells_counter = 0;
    marks_counter = 0;

    ResetData();
}

void FieldView::HideMine()
{
    for (auto& cell : cells) {
        cell->Unblock();
    }
    cells[opened_mine]->Hide();
}

void FieldView::ResetData()
{
    if (data != nullptr) delete data;
    data = new FieldData(rows, cols, mines);
    for (int i = 0; i < rows * cols; i++) {
        cells[i]->SetData(&data->GetCellData(i));
    }
}

void FieldView::ResetField()
{
    QGridLayout* field_lay = new QGridLayout(this);
    field_lay->setSizeConstraint(QLayout::SetFixedSize);
    field_lay->setHorizontalSpacing(0);
    field_lay->setVerticalSpacing(0);

    for (int i = 0; i < rows * cols; i++) {
        MakeCell(i);
        field_lay->addWidget(cells[i], i / cols, i % cols);
    }

    //layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void FieldView::MakeCell(int id)
{
    cells.push_back(new CellView(id, this));

    connect(cells[id], &CellView::Clicked, this, &FieldView::Clicked);
    connect(cells[id], &CellView::MineOpened, this, &FieldView::Boom);

    connect(cells[id], &CellView::CounterOpened, this, [this](){
        detected_cells_counter++;
        CheckIsCompleted();
    });

    connect(cells[id], &CellView::VoidOpened, this, [this](int id){
        detected_cells_counter++;
        OpenVoidArea(id);
        CheckIsCompleted();
    });

    connect(cells[id], &CellView::Marked, this, [this](){
        marks_counter++;
        detected_cells_counter++;
        CheckIsCompleted();
        emit MarksCounterChanged(marks_counter);
    });

    connect(cells[id], &CellView::Unmarked, this, [this](){
        marks_counter--;
        detected_cells_counter--;
        emit MarksCounterChanged(marks_counter);
    });
}

void FieldView::CheckIsCompleted()
{
    if ((marks_counter == mines) && (detected_cells_counter == cells.size())) {
        emit FieldIsCompleted();
    }
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
    for (auto& cell : cells) {
        cell->Block();
    }
    opened_mine = id_mine;
    emit FieldIsBoomed();
}
