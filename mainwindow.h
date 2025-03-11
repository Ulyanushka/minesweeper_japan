#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>

#include "field/field_view.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void NewGame(int rows, int cols, int mines);

private:
    void SetupGameoverMsgBox();
    void ResetMinesData();
    void SetupResetBtn();
    void SetupField();
    void SetupSetuperBtn();

    void GameOver();
    void ResetField();

    void SetMinesData(int counter);
    void SetFieldData();
    void ChangeFieldData();

private:
    QLabel mines_data;
    QPushButton reset_btn;
    QLabel field_data;
    QPushButton setuper_btn;

    int rows, cols, mines = 0;
    FieldView* field = nullptr;

    QMessageBox gameover_msgbox;
    QPushButton again_btn;
};

#endif // MAINWINDOW_H
