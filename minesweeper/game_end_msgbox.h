#ifndef GAMEENDMSGBOX_H
#define GAMEENDMSGBOX_H

#include <QMessageBox>
#include <QPushButton>


class GameEndMsgBox : public QMessageBox
{
    Q_OBJECT
public:
    GameEndMsgBox(const QString& title, const QString& msg,
                  const QString& again_btn_text,
                  const QString& continue_btn_txt,
                  QWidget* parent = nullptr);
    ~GameEndMsgBox() = default;

signals:
    void AgainClicked();
    void ContinueClicked();

private:
    QPushButton* again_btn;
    QPushButton* continue_btn;
};

#endif // GAMEENDMSGBOX_H
