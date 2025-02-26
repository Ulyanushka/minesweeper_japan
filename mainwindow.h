#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "field/field_view.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void SetField(int rows, int cols, int mines);

private:
    FieldView* field = nullptr;
};

#endif // MAINWINDOW_H
