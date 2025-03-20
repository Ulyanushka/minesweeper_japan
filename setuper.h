#ifndef SETUPER_H
#define SETUPER_H

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>


struct MinesweeperSettings
{
    bool operator==(const MinesweeperSettings& other) const;
    bool IsSameSize(const MinesweeperSettings& other) const;

    int CountCells() const;
    int CountMinesPercent() const;
    bool AreMinesValid() const;

    int rows = 16;
    int cols = 16;
    int mines = 40;
};

struct QuizSettings
{
    int num_of_answers = 8;
    int num_of_questions_for_succes = 1;
    QStringList databases = {"data/jap_kanji_n5.json"};
};


class Setuper : public QWidget
{
    Q_OBJECT
public:
    Setuper(MinesweeperSettings* minesweeper_settings,
            QuizSettings* quiz_settings,
            QWidget* parent = nullptr);
    ~Setuper();

signals:
    void FieldSizeChanged();
    void FieldDetailsChanged();

    void FieldSettingsChanged();

private:
    void SetupUI();
    void SetupBtns();

    void SetCurrentData();
    void UpdateAdditionalData();
    void UpdateMinesData();

    int CountCells();
    void CheckChanges();

private:
    MinesweeperSettings* cur_minesweeper_settings = nullptr;
    MinesweeperSettings temp_minesweeper_settings;

    QuizSettings* cur_quiz_settings = nullptr;
    QuizSettings temp_quiz_settings;

    QLineEdit* rows_le;
    QLineEdit* cols_le;
    QLabel* size_lbl;
    QLineEdit* mines_le;
    QLabel* mines_lbl;

    QPushButton* cancel_btn;
    QPushButton* save_btn;
};

#endif // SETUPER_H
