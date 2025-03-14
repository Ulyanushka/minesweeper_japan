#ifndef QUIZDATA_H
#define QUIZDATA_H

#include <QList>

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

#endif // QUIZDATA_H
