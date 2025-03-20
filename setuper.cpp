#include "setuper.h"

#include <QLayout>
#include <QValidator>
#include <QDebug>


//SETTINGS-----------------------------------------------------------------------------------------

bool MinesweeperSettings::operator==(const MinesweeperSettings& other) const
{
    return ((rows == other.rows)
            && (cols == other.cols)
            && (mines == other.mines));
}

bool MinesweeperSettings::IsSameSize(const MinesweeperSettings& other) const
{
    return ((rows == other.rows)
            && (cols == other.cols));
}

int MinesweeperSettings::CountCells() const
{
    return rows*cols;
}

int MinesweeperSettings::CountMinesPercent() const
{
    return (CountCells() == 0) ? 0 : mines*100/CountCells();
}

bool MinesweeperSettings::AreMinesValid() const
{
    return ((mines > 0) && (mines < CountCells()));
}


//SETUPER------------------------------------------------------------------------------------------

inline static const char* invalid_color = "background-color: rgba(185, 29, 113, 0.4);";
inline static const char* valid_color = "background-color: ;";


Setuper::Setuper(MinesweeperSettings* minesweeper_settings,
                 QuizSettings* quiz_settings,
                 QWidget* parent)
    : QWidget(parent),
    cur_minesweeper_settings(minesweeper_settings),
    temp_minesweeper_settings(*minesweeper_settings),
    cur_quiz_settings(quiz_settings),
    temp_quiz_settings(*quiz_settings)
{
    setWindowTitle("Settings");

    QGridLayout* main_lay = new QGridLayout(this);
    main_lay->setHorizontalSpacing(10);
    main_lay->setVerticalSpacing(10);

    SetupUI();
    SetCurrentData();

    main_lay->addWidget(new QLabel("Rows:\n(max 30)"), 1, 0);
    main_lay->addWidget(rows_le, 1, 1);
    main_lay->addWidget(new QLabel("Columns:\n(max 30)"), 2, 0);
    main_lay->addWidget(cols_le, 2, 1);
    main_lay->addWidget(size_lbl, 3, 0, 1, 2, Qt::AlignHCenter);

    main_lay->addWidget(new QLabel("Mines:\n(15-20% is best)"), 4, 0);
    main_lay->addWidget(mines_le, 4, 1);
    main_lay->addWidget(mines_lbl, 5, 0, 1, 2, Qt::AlignHCenter);

    SetupBtns();
    main_lay->addWidget(cancel_btn, 6, 0, Qt::AlignHCenter);
    main_lay->addWidget(save_btn, 6, 1, Qt::AlignHCenter);

    setFixedSize(minimumSize());
}

Setuper::~Setuper()
{
    cur_minesweeper_settings = nullptr;
}

void Setuper::SetupUI()
{
    QRegularExpression side_regexp("[1-9]|[1-2][0-9]|30");
    QValidator* side_validator = new QRegularExpressionValidator(side_regexp, this);

    rows_le = new QLineEdit(this);
    rows_le->setValidator(side_validator);
    connect(rows_le, &QLineEdit::textEdited, this, [this](){
        temp_minesweeper_settings.rows = rows_le->text().toInt();
        CheckChanges();
        UpdateAdditionalData();
    });

    cols_le = new QLineEdit(this);
    cols_le->setValidator(side_validator);
    connect(cols_le, &QLineEdit::textEdited, this, [this](){
        temp_minesweeper_settings.cols = cols_le->text().toInt();
        CheckChanges();
        UpdateAdditionalData();
    });

    size_lbl = new QLabel(this);

    mines_le = new QLineEdit(this);
    connect(mines_le, &QLineEdit::textEdited, this, [this](){
        temp_minesweeper_settings.mines = mines_le->text().toInt();
        CheckChanges();
        UpdateMinesData();
    });

    mines_lbl = new QLabel(this);
}

void Setuper::SetupBtns()
{
    cancel_btn = new QPushButton("Cancel", this);
    cancel_btn->setDisabled(true);
    connect(cancel_btn, &QPushButton::clicked, this, [this]() {
        temp_minesweeper_settings = *cur_minesweeper_settings;
        SetCurrentData();
    });

    save_btn = new QPushButton("Save", this);
    save_btn->setDisabled(true);
    connect(save_btn, &QPushButton::clicked, this, [this](){
        bool is_size_changed = !cur_minesweeper_settings->IsSameSize(temp_minesweeper_settings);
        *cur_minesweeper_settings = temp_minesweeper_settings;
        (is_size_changed) ? emit FieldSizeChanged() : emit FieldDetailsChanged();
    });
}

void Setuper::SetCurrentData()
{
    rows_le->setText(QString::number(cur_minesweeper_settings->rows));
    cols_le->setText(QString::number(cur_minesweeper_settings->cols));
    mines_le->setText(QString::number(cur_minesweeper_settings->mines));

    UpdateAdditionalData();
}

void Setuper::UpdateAdditionalData()
{
    size_lbl->setText(QString("Cells: %1").arg(temp_minesweeper_settings.CountCells()));
    UpdateMinesData();
}

void Setuper::UpdateMinesData()
{
    mines_lbl->setText(QString("Mines are %1% of all cells")
                           .arg(temp_minesweeper_settings.CountMinesPercent()));

    mines_le->setStyleSheet(temp_minesweeper_settings.AreMinesValid() ? valid_color : invalid_color);
    if (!temp_minesweeper_settings.AreMinesValid()) {
        save_btn->setDisabled(true);
    }
}

void Setuper::CheckChanges()
{
    bool data_changed = !(*cur_minesweeper_settings == temp_minesweeper_settings);

    save_btn->setEnabled(data_changed);
    cancel_btn->setEnabled(data_changed);
}
