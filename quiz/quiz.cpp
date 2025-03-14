#include "quiz.h"

#include <QGridLayout>


Quiz::Quiz(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Quiz Time!");

    int num_of_answers = 8;

    QGridLayout* main_lay = new QGridLayout(this);
    main_lay->setHorizontalSpacing(10);
    main_lay->setVerticalSpacing(5);

    question_lbl = new QLabel("QUESTION", this);
    main_lay->addWidget(question_lbl, 0, 0, num_of_answers/2, 1, Qt::AlignHCenter);

    for (int i = 0; i < num_of_answers; i++) {
        answers_lbls.append(new QLabel(QString("Answer %1").arg(i), this));
        main_lay->addWidget(answers_lbls[i], i%4, i/4+1, Qt::AlignHCenter);
    }
}
