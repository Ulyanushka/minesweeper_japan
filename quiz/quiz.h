#ifndef QUIZ_H
#define QUIZ_H

#include <QLabel>
#include <QPushButton>>

#include "quiz_data.h"
#include "data_reader.h"


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

public:
    void LoadData(QString& file_path);

private:
    QLabel* question_lbl;
    QList<QPushButton*> answers_btns;

    QuizStatData stats;
    DataReader* reader;
    QuizData* data;
};

#endif // QUIZ_H
