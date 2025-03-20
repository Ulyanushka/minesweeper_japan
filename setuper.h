#ifndef SETUPER_H
#define SETUPER_H

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>


struct Settings
{
    bool operator==(const Settings& other) const;
    bool IsSameSize(const Settings& other) const;

    int CountCells() const;
    int CountMinesPercent() const;
    bool AreMinesValid() const;

    int rows = 16;
    int cols = 16;
    int mines = 40;
};


class Setuper : public QWidget
{
    Q_OBJECT
public:
    Setuper(Settings* settings, QWidget* parent = nullptr);
    ~Setuper();

signals:
    void FieldSizeChanged();
    void FieldDetailsChanged();

    void FieldSettingsChanged();

private:
    void SetupUI();
    void SetupBtns();

    void SetCurrentData();
    void UpdateAdditionalData();
    void UpdateMinesData();

    int CountCells();
    void CheckChanges();

private:
    Settings* cur = nullptr;
    Settings temp;

    QLineEdit* rows_le;
    QLineEdit* cols_le;
    QLabel* size_lbl;
    QLineEdit* mines_le;
    QLabel* mines_lbl;

    QPushButton* cancel_btn;
    QPushButton* save_btn;
};

#endif // SETUPER_H
