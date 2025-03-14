#ifndef QUIZ_H
#define QUIZ_H

#include <QObject>
#include <QWidget>

#include "data_reader.h"


struct QuizItem
{

};

struct QuizData
{

};

class Quiz : public QWidget
{
    Q_OBJECT
public:
    Quiz(QWidget* parent = nullptr);
    ~Quiz() = default;

private:
    DataReader* reader;

};

#endif // QUIZ_H
