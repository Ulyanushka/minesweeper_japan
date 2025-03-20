#ifndef QUIZDATA_H
#define QUIZDATA_H

#include <QList>
#include <list>


struct QuizStatData
{
    int wins = 0;
    int fails = 0;
    int all_questions = 0;
    int opened_questions = 0;
};


struct MetaData
{
    QString title = "title";
    QString items = "items";

    QString id = "id";
    QString term = "term";
    QString definition = "definition";
};


struct DataItem
{
    QString GetStrForDebug();

    int id;
    QString term;
    QString definition;
};


class QuizData
{
public:
    QuizData(const QString& title, const QList<DataItem>& data);
    ~QuizData() = default;

    DataItem* GetQuestionData();
    QStringList GetBadAnswers(int right_answer_id, int num_of_answers);

private:
    int GetRandomItemId();

private:
    //QList<int> passed_questions;

    QString title;
    QList<DataItem> data;
};

#endif // QUIZDATA_H
