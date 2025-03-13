#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>

#include "minesweeper/field_view.h"
#include "minesweeper/stat_data.h"
#include "setuper.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

private:
    void SetupMsgBoxes();
    void SetupSetuper();

    void SetupUI();
    void SetupField();

    void RebuildField();
    void ResetField();
    void ResetStats();

    void ForgiveMistake();
    void GameOver();
    void Win();

private:
    StatData* stats;
    QPushButton* reset_btn;
    QPushButton* setuper_btn;

    Setuper* setuper;
    Settings settings;
    FieldView* field = nullptr;

    QMessageBox* looser_msgbox;
    QPushButton* again_for_loosers_btn;
    QPushButton* sorry_btn;

    QMessageBox* winner_msgbox;
    QPushButton* again_for_winners_btn;
    QPushButton* super_btn;
};

#endif // MAINWINDOW_H
