#include "quiz.h"

#include <QGridLayout>
#include <QVboxLayout>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QRandomGenerator>
#include <QMouseEvent>
#include <QString>


//ANSWER_BTN---------------------------------------------------------------------------------------

inline static const char* answer_font_size = "font-size: 15px;";

inline static const char* hided_answer_btn_color = "background-color: rgba(150, 150, 150, 0.4);";
inline static const char* good_answer_btn_color = "background-color: rgba(46, 204, 113, 0.4);";
inline static const char* bad_answer_btn_color = "background-color: rgba(185, 29, 113, 0.4);";

inline static const char* clicked_btn_border = "border-style: outset; border-width: 5px; border-color: rgba(200, 255 , 0, 1.0);";
inline static const char* not_clicked_btn_border = "border-width: 0px;";


AnswerBtn::AnswerBtn(QWidget* parent) : QPushButton(parent)
{
    setStyleSheet(answer_font_size);
    setFixedSize(100, 30);
}

void AnswerBtn::SetAnswer(const QString& text, bool is_good)
{
    setText(text);
    is_good_answer = is_good;
    is_chosen = false;
    Hide();
}

void AnswerBtn::mousePressEvent(QMouseEvent* e)
{
    if (!is_blocked && e->button() == Qt::LeftButton) {
        is_chosen = true;
        (is_good_answer) ? emit GoodAnswerClicked() : emit BadAnswerCLicked();
    }
}

void AnswerBtn::Hide()
{
    is_blocked = false;
    clicked(false);
    setStyleSheet(hided_answer_btn_color);
}

void AnswerBtn::Reveal()
{
    is_blocked = true;
    QString stylesheet;
    (is_good_answer) ? stylesheet.append(good_answer_btn_color)
                     : stylesheet.append(bad_answer_btn_color);
    if (is_chosen) stylesheet.append(clicked_btn_border);
    setStyleSheet(stylesheet);
}


//QUIZ---------------------------------------------------------------------------------------------

inline static const char* question_font_size = "font-size: 50px;";


Quiz::Quiz(int num_of_questions, int num_of_answers, QWidget* parent)
    : QWidget(parent), num_of_question_to_pass(num_of_questions), passed_questions(0)
{   
    setWindowTitle("Quiz Time!");
    setWindowFlag(Qt::WindowCloseButtonHint, false);

    QVBoxLayout* main_lay = new QVBoxLayout(this);

    QWidget* quiz_w = new QWidget(this);
    QGridLayout* quiz_lay = new QGridLayout(quiz_w);
    quiz_lay->setHorizontalSpacing(10);
    quiz_lay->setVerticalSpacing(5);

    question_lbl = new QLabel(this);
    question_lbl->setStyleSheet(question_font_size);
    quiz_lay->addWidget(question_lbl, 0, 0, num_of_answers/2, 1, Qt::AlignHCenter);

    for (int i = 0; i < num_of_answers; i++) {
        CreateAnswerBtn();
        quiz_lay->addWidget(answers_btns[i], i%4, i/4+1, Qt::AlignHCenter);
    }

    main_lay->addWidget(quiz_w, Qt::AlignHCenter);

    QWidget* res_w = new QWidget(this);
    QVBoxLayout* res_lay = new QVBoxLayout(res_w);

    SetupResultUI();
    res_lay->addWidget(questions_to_pass, Qt::AlignHCenter);
    res_lay->addWidget(result, Qt::AlignHCenter);
    res_lay->addWidget(accept_result_btn, Qt::AlignHCenter);
    res_lay->addWidget(next_question_btn, Qt::AlignHCenter);

    main_lay->addWidget(res_w, Qt::AlignHCenter);

    setFixedSize(minimumSize());
}

Quiz::~Quiz()
{
    if (quiz_data != nullptr) {
        delete quiz_data;
        quiz_data = nullptr;
    }
}

void Quiz::SetNumOfQuestions(int num)
{
    num_of_question_to_pass = num;
}

void Quiz::SetNumOfAnswers(int num)
{

}

void Quiz::SetData(const QStringList& files_pathes)
{
    if (quiz_data != nullptr) delete quiz_data;

    QList<DataItem> data;
    for (const auto& file_path : files_pathes) {
        data.append(GetDataFromJson(file_path));
    }

    quiz_data = new QuizData(data);
}

void Quiz::Start()
{
    show();
    is_passed = false;
    passed_questions = 0;
    SetQuestion();
}

void Quiz::CreateAnswerBtn()
{
    answers_btns.append(new AnswerBtn(this));
    connect(answers_btns.last(), &AnswerBtn::GoodAnswerClicked, this, [this]() {
        quiz_data->MarkThisQuestionPassed(cur_question_id);
        RevealAllAnswers();
        passed_questions++;
        if (passed_questions == num_of_question_to_pass) {
            is_passed = true;
        }
        SetResultData("You are such a beauty!", (is_passed) ? "Continue Game" : "Accept GameOver", true, true);
    });
    connect(answers_btns.last(), &AnswerBtn::BadAnswerCLicked, this, [this]() {
        RevealAllAnswers();
        (is_passed) ? SetResultData("Wrong answer, but you had a right one.", "Continue Game", true, true)
                    : SetResultData("Oh poor gamer...", "Accept GameOver", true, true);
    });
}

void Quiz::SetupResultUI()
{
    questions_to_pass = new QLabel(this);
    result = new QLabel(this);

    accept_result_btn = new QPushButton(this);
    connect(accept_result_btn, &QPushButton::clicked, this, [this]() {
        close();
        (is_passed) ? emit Passed() : emit Failed();
    });

    next_question_btn = new QPushButton("Next please", this);
    connect(next_question_btn, &QPushButton::clicked, this, &Quiz::SetQuestion);
}

void Quiz::SetQuestion()
{
    DataItem* question = quiz_data->GetQuestionData();
    cur_question_id = question->id;
    question_lbl->setText(question->term);

    QStringList bad_answers = quiz_data->GetBadAnswers(question->id, answers_btns.size()-1);
    for (int i = 0; i < bad_answers.size(); i++) {
        answers_btns[i]->SetAnswer(bad_answers[i], false);
    }
    answers_btns.last()->SetAnswer(question->definition, true); //good answer

    HideGoodAnswer(answers_btns.size()-1);
    (is_passed) ? SetResultData("Choose wisely!", "Continue Game", true, false)
                : SetResultData("Choose wisely!", "No escape", false, false);
}

void Quiz::HideGoodAnswer(int good_answer_id)
{
    int new_id = QRandomGenerator::global()->bounded(answers_btns.size());
    answers_btns.swapItemsAt(good_answer_id, new_id);
}

void Quiz::RevealAllAnswers()
{
    for (auto& answer_btn : answers_btns) {
        answer_btn->Reveal();
    }
}

void Quiz::SetResultData(const QString& status, const QString& accept_btn_text,
                         bool is_there_escape, bool is_question_done)
{
    questions_to_pass->setText(QString("Passed Questions: %1/%2")
                                   .arg(passed_questions).arg(num_of_question_to_pass));
    result->setText(status);
    accept_result_btn->setText(accept_btn_text);
    accept_result_btn->setEnabled(is_there_escape);
    next_question_btn->setEnabled(is_question_done);
}

QList<DataItem> Quiz::GetDataFromJson(const QString& file_path)
{
    QList<DataItem> data;

    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "bad file";
        return data;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if(doc.isNull()) {
        qDebug() << "bad json";
        return data;
    }
    qDebug() << "file and json are ok";

    QJsonArray items = doc.object()[meta.items].toArray();
    for (const auto& item_value : items) {
        QJsonObject item = item_value.toObject();

        DataItem data_item;
        data_item.id = item[meta.id].toInt();
        data_item.term = item[meta.term].toString();
        data_item.definition = item[meta.definition].toString();

        //qDebug() << data_item.GetStrForDebug();
        data.append(data_item);
    }
    return data;
}
