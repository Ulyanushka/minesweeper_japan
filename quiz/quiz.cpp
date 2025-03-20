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


Quiz::Quiz(QWidget* parent) : QWidget(parent)
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

    result = new QLabel(this);
    res_lay->addWidget(result, Qt::AlignHCenter);

    SetupBtns();
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

void Quiz::SetData(const QString& file_path)
{
    LoadJsonFile(file_path);
}

void Quiz::Start()
{
    show();
    is_passed = false;
    SetQuestion();
}

void Quiz::CreateAnswerBtn()
{
    answers_btns.append(new AnswerBtn(this));
    connect(answers_btns.last(), &AnswerBtn::GoodAnswerClicked, this, [this]() {
        quiz_data->MarkThisQuestionPassed(cur_question_id);
        RevealAllAnswers();
        SetResultData("You are such a beauty!", "Continue Game", true, true);
        is_passed = true;
    });
    connect(answers_btns.last(), &AnswerBtn::BadAnswerCLicked, this, [this]() {
        RevealAllAnswers();
        (is_passed) ? SetResultData("Wrong answer, but you had a right one.", "Continue Game", true, true)
                    : SetResultData("Oh poor gamer...", "Accept GameOver", true, true);
    });
}

void Quiz::SetupBtns()
{
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
    answers_btns[0]->SetAnswer(question->definition, true); //good answer

    QStringList bad_answers = quiz_data->GetBadAnswers(question->id, num_of_answers);
    for (int i = 1; i < num_of_answers; i++) {
        answers_btns[i]->SetAnswer(bad_answers[i], false);
    }

    HideGoodAnswer();
    (is_passed) ? SetResultData("Choose wisely!", "Continue Game", true, false)
                : SetResultData("Choose wisely!", "No escape", false, false);
}

void Quiz::HideGoodAnswer(int good_answer_id)
{
    int new_id = QRandomGenerator::global()->bounded(num_of_answers);
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
    result->setText(status);
    accept_result_btn->setText(accept_btn_text);
    accept_result_btn->setEnabled(is_there_escape);
    next_question_btn->setEnabled(is_question_done);
}

void Quiz::LoadJsonFile(const QString& file_path)
{
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "bad file";
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if(doc.isNull()) {
        qDebug() << "bad json";
        return;
    }
    qDebug() << "file and json are ok";

    QString title = doc.object()[meta.title].toString();
    QList<DataItem> data;

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

    if (quiz_data != nullptr) delete quiz_data;
    quiz_data = new QuizData(title, data);
}
