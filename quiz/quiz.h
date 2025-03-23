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
    Quiz(int num_of_questions = 3, int num_of_answers = 8,
         const QuizData& quiz_data = QuizData(),
         QWidget* parent = nullptr);
    ~Quiz() = default;

public:
    void SetNumOfQuestions(int num);
    void SetData(const QStringList& files_pathes);
    void SetData(const QuizData& new_quiz_data);

    QuizData GetData() const;

    void Start();

signals:
    void Passed();
    void Failed();

private:
    void CreateAnswerBtn();
    void SetupResultUI();

    void SetQuestion();
    void HideGoodAnswer(int good_answer_id);
    void RevealAllAnswers();

    void SetResultData(const QString& status, const QString& accept_btn_text,
                       bool is_there_escape, bool is_question_done);

    QList<DataItem> GetDataFromJson(const QString& file_path) const;

private:
    QLabel* question_lbl;
    int cur_question_id;

    QList<AnswerBtn*> answers_btns;

    bool is_passed;
    int num_of_question_to_pass;
    int passed_questions;

    QLabel* questions_to_pass;
    QLabel* result;

    QPushButton* accept_result_btn;
    QPushButton* next_question_btn;

    QuizStatData stats;
    QuizData quiz_data;
    MetaData meta;
};

#endif // QUIZ_H
