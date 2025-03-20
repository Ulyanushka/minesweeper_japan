#ifndef QUIZ_H
#define QUIZ_H

#include <QLabel>
#include <QPushButton>

#include "quiz_data.h"


class AnswerBtn : public QPushButton
{
    Q_OBJECT
public:
    AnswerBtn(QWidget* parent = nullptr);
    ~AnswerBtn() = default;

    void SetAnswer(const QString& text, bool is_good);
    void Reveal();

signals:
    void GoodAnswerClicked();
    void BadAnswerCLicked();

protected:
    void mousePressEvent(QMouseEvent* e) override;

private:
    void Hide();

private:
    bool is_blocked;
    bool is_chosen;
    bool is_good_answer;
};


class Quiz : public QWidget
{
    Q_OBJECT
public:
    Quiz(QWidget* parent = nullptr);
    ~Quiz();

public:
    void SetNumOfAnswers(int num);
    void SetData(const QStringList& files_pathes);
    void Start();

signals:
    void Passed();
    void Failed();

private:
    void CreateAnswerBtn();
    void SetupBtns();

    void SetQuestion();
    void HideGoodAnswer(int good_answer_id = 0);
    void RevealAllAnswers();

    void SetResultData(const QString& status, const QString& accept_btn_text,
                       bool is_there_escape, bool is_question_done);
    QList<DataItem> GetDataFromJson(const QString& file_path);

private:
    QLabel* question_lbl;
    int cur_question_id;

    int num_of_answers = 8;
    QList<AnswerBtn*> answers_btns;

    bool is_passed;
    QLabel* result;
    QPushButton* accept_result_btn;
    QPushButton* next_question_btn;

    QuizStatData stats;
    QuizData* quiz_data = nullptr;
    MetaData meta;
};

#endif // QUIZ_H
