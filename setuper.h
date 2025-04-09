#ifndef SETUPER_H
#define SETUPER_H

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>


struct MinesweeperSettings
{
    bool operator==(const MinesweeperSettings& other) const;
    bool IsSameSize(const MinesweeperSettings& other) const;

    int GetCellsCounter() const;
    int GetMinesPercent() const;
    bool AreMinesValid() const;

    int rows = 16;
    int cols = 16;
    int mines = 40;
};

struct QuizSettings
{
    int num_of_answers = 8;
    int num_of_questions_for_succes = 3;
    QStringList databases = {"data/jap_kanji_n5.json"};
};


class MinesweeperSetuper : public QWidget
{
    Q_OBJECT
public:
    MinesweeperSetuper(MinesweeperSettings* settings, QWidget* parent = nullptr);
    ~MinesweeperSetuper();

signals:
    void SizeChanged();
    void MinesNumChanged();

private:
    void SetupUI();
    void SetupBtns();

    void SetCurrentData();
    void UpdateAdditionalData();
    void UpdateMinesData();

    int CountCells();
    void CheckChanges();

private:
    MinesweeperSettings* cur = nullptr;
    MinesweeperSettings temp;

    QLineEdit* rows_le;
    QLineEdit* cols_le;
    QLabel* size_lbl;
    QLineEdit* mines_le;
    QLabel* mines_lbl;

    QPushButton* cancel_btn;
    QPushButton* save_btn;
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
    void MinesweeperSizeChanged();
    void MinesweeperMinesNumChanged();

    void QuizNumOfAnswersChanged();
    void QuizNumOfQuestionsChanged();
    void QuizDatabasesChanged();

private:
    MinesweeperSetuper* minesweeper_setuper = nullptr;
};

#endif // SETUPER_H
