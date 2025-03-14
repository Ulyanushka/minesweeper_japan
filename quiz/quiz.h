#ifndef QUIZ_H
#define QUIZ_H

#include <QObject>
#include <QWidget>

#include "data_reader.h"


enum class Example {
    Word,
    Reading,
    Definition
};


struct DataItem
{
    int id;
    QString character;
    QString definition;
    QStringList example_1;
    QStringList example_2;
};


class QuizData
{
public:
    QuizData(const QString& title, const QList<DataItem>& data);
    ~QuizData() = default;

    DataItem* GetQuestionData();
    QStringList GetWrongAnswers(int right_answer_id, int num_of_answers);

private:
    DataItem* GetRandomItem();

private:
    QList<DataItem> data;
};


struct QuizStatData
{
    int wins = 0;
    int fails = 0;
    int all_questions = 0;
    int opened_questions = 0;
};


class Quiz : public QWidget
{
    Q_OBJECT
public:
    Quiz(QWidget* parent = nullptr);
    ~Quiz() = default;

private:
    QuizStatData stats;
    DataReader* reader;
    QuizData* data;
};

#endif // QUIZ_H
