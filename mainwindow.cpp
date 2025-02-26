#include "mainwindow.h"

#include <QVBoxLayout>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    QVBoxLayout* lay = new QVBoxLayout();
    SetField(16,16,40);
    lay->addWidget(field);

    QWidget* w = new QWidget();
    w->setLayout(lay);
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    if (field != nullptr) delete field;
    field = nullptr;
}

void MainWindow::SetField(int rows, int cols, int mines)
{
    if (field != nullptr) delete field;
    field = new FieldView(rows, cols, mines);
}
