#include "field_view.h"

#include <QGridLayout>


//Q_GLOBAL_STATIC_WITH_ARGS(QString, normal_btn_color, ("background-color: rgba(46, 204, 113, 0.4);"))

inline static const char* normal_btn_color = "background-color: rgba(46, 204, 113, 0.4);";
inline static const char* marked_btn_color = "background-color: rgba(46, 204, 113, 0.8);";
inline static const char* clicked_btn_color = "background-color: rgba(0,0,0,0);";


CellView::CellView(const QString& data, QWidget* parent)
    : QPushButton(parent), text(data)
{
    is_void = (text.isEmpty());
    is_mine = (text == "M");

    setFixedSize(20, 20);
    setStyleSheet(normal_btn_color);
}

void CellView::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) Uncover();
    else if (e->button() == Qt::RightButton) Mark();
}

void CellView::Uncover()
{
    setText(text);
    setStyleSheet(clicked_btn_color);
}

void CellView::Mark()
{
    setStyleSheet(marked_btn_color);
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
        cells.push_back(new CellView(data->GetCellData(i)));
        grid_lay->addWidget(cells[i], i / cols, i % cols);
    }

    setLayout(grid_lay);
}
