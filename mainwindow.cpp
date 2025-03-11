#include "mainwindow.h"

#include <QVBoxLayout>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    rows = 16;
    cols = 16;
    mines = 40;

    SetupGameoverMsgBox();

    QGridLayout* data_lay = new QGridLayout();
    data_lay->setHorizontalSpacing(10);
    data_lay->setVerticalSpacing(5);

    SetMinesData(0);
    data_lay->addWidget(&mines_data, 0, 0, 2, 1, Qt::AlignHCenter);
    SetupResetBtn();
    data_lay->addWidget(&reset_btn, 0, 1, 2, 1, Qt::AlignHCenter);
    SetFieldData();
    data_lay->addWidget(&field_data, 0, 2, 2, 1, Qt::AlignHCenter);
    //SetupSetuperBtn();
    //data_lay->addWidget(&setuper_btn, 1, 2, Qt::AlignHCenter);

    QVBoxLayout* main_lay = new QVBoxLayout();
    main_lay->addLayout(data_lay);
    SetupField();
    main_lay->addWidget(field);

    QWidget* w = new QWidget();
    w->setLayout(main_lay);
    setCentralWidget(w);

    //setFixedSize(minimumSize());
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

MainWindow::~MainWindow()
{
    if (field != nullptr) delete field;
    field = nullptr;
}

void MainWindow::SetupGameoverMsgBox()
{
    gameover_msgbox.setText("FIeld is boomed.\nGame over.");
    again_btn.setText("Again");
    gameover_msgbox.addButton(&again_btn, QMessageBox::ActionRole);
}

void MainWindow::SetupResetBtn()
{
    reset_btn.setText("Reset");
    connect(&reset_btn, &QPushButton::clicked, this, &MainWindow::ResetField);
}

void MainWindow::SetupField()
{
    if (field != nullptr) delete field;
    field = new FieldView(rows, cols, mines);
    connect(field, &FieldView::FieldIsBoomed, this, &MainWindow::GameOver);
    connect(field, &FieldView::MarksCounterChanged, this, &MainWindow::SetMinesData);
}

void MainWindow::SetupSetuperBtn()
{
    setuper_btn.setText("Change...");
    connect(&reset_btn, &QPushButton::clicked, this, &MainWindow::ChangeFieldData);
}

void MainWindow::GameOver()
{
    gameover_msgbox.exec();
    if(gameover_msgbox.clickedButton() == &again_btn) {
        ResetField();
    }
}

void MainWindow::ResetField()
{
    field->Reset();
    SetMinesData(0);
}

void MainWindow::SetMinesData(int counter)
{
    mines_data.setText(QString("Marks/Mines:\n%1/%2").arg(counter).arg(mines));
}

void MainWindow::SetFieldData()
{
    auto cells = rows*cols;
    field_data.setText(QString("Field: %1x%2 (%3 cells)\nMines: %4 (%5%)")
                           .arg(rows).arg(cols).arg(cells).arg(mines).arg(mines*100/cells));
}

void MainWindow::ChangeFieldData()
{

}
