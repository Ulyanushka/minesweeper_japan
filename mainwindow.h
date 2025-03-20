#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>

#include "quiz/quiz.h"
#include "minesweeper/game_end_msgbox.h"
#include "minesweeper/field_view.h"
#include "minesweeper/stat_data.h"
#include "setuper.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void SetupQuiz();

    void SetupMsgBoxes();
    void SetupSetuper();

    void SetupUI();
    void SetupField();

    void RebuildField();
    void ResetField();
    void ResetStats();

    void ForgiveMistake();

private:
    //QPushButton* quiz_btn;
    Quiz* quiz;

    GameEndMsgBox* loose_game_msgbox;
    GameEndMsgBox* win_game_msgbox;

    Setuper* setuper;
    Settings settings;

    StatData* stats;
    QPushButton* reset_btn;
    QPushButton* setuper_btn;

    FieldView* field = nullptr;
};

#endif // MAINWINDOW_H
