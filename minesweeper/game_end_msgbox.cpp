#include "game_end_msgbox.h"


GameEndMsgBox::GameEndMsgBox(const QString& title, const QString& msg,
                             const QString& again_btn_text,
                             const QString& continue_btn_txt,
                             QWidget* parent)
    : QMessageBox(parent)
{
    setWindowTitle(title);
    setText(msg);

    again_btn = new QPushButton(again_btn_text, this);
    addButton(again_btn, QMessageBox::ActionRole);
    connect(again_btn, &QPushButton::clicked, this, &GameEndMsgBox::AgainClicked);

    continue_btn = new QPushButton(continue_btn_txt, this);
    addButton(continue_btn, QMessageBox::ActionRole);
    connect(continue_btn, &QPushButton::clicked, this, &GameEndMsgBox::ContinueClicked);
}
