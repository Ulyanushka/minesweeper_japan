#include "quiz_data.h"

#include <QRandomGenerator>
#include <QSet>


//DATA_ITEM----------------------------------------------------------------------------------------

QString DataItem::GetStrForDebug()
{
    return QString("id: %1 \n%2 - %3").arg(id).arg(term).arg(definition);
}


//QUIZ_DATA----------------------------------------------------------------------------------------

QuizData::QuizData(const QString& title, const QList<DataItem>& data)
    : title(title), data(data)
{

}

DataItem* QuizData::GetQuestionData()
{
    return &data[GetRandomItemId()];
}

QStringList QuizData::GetBadAnswers(int right_answer_id, int num_of_answers)
{
    QSet<int> answers_ids;

    while (answers_ids.size() < num_of_answers) {
        int id = GetRandomItemId();
        if (id != right_answer_id) {
            answers_ids.insert(id);
        }
    }

    QStringList answers;
    for (const auto& answer_id : answers_ids) {
        answers.append(data[answer_id].definition);
    }
    return answers;
}

int QuizData::GetRandomItemId()
{
    return QRandomGenerator::global()->bounded(data.size());
}
