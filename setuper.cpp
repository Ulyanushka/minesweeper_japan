#include "setuper.h"

#include <QLayout>
#include <QValidator>
#include <QDebug>
#include <QTabWidget>


inline static const char* invalid_color = "background-color: rgba(185, 29, 113, 0.4);";
inline static const char* valid_color = "background-color: ;";


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

int MinesweeperSettings::GetCellsCounter() const
{
    return rows*cols;
}

int MinesweeperSettings::GetMinesPercent() const
{
    return (GetCellsCounter() == 0) ? 0 : mines*100/GetCellsCounter();
}

bool MinesweeperSettings::AreMinesValid() const
{
    return ((mines > 0) && (mines < GetCellsCounter()));
}

//MINESWEEPER_SETUPER------------------------------------------------------------------------------
MinesweeperSetuper::MinesweeperSetuper(MinesweeperSettings* settings, QWidget* parent)
    : QWidget(parent), cur(settings), temp(*settings)
{
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
}

MinesweeperSetuper::~MinesweeperSetuper()
{
    cur = nullptr;
}

void MinesweeperSetuper::SetupUI()
{
    QRegularExpression side_regexp("[1-9]|[1-2][0-9]|30");
    QValidator* side_validator = new QRegularExpressionValidator(side_regexp, this);

    rows_le = new QLineEdit(this);
    rows_le->setValidator(side_validator);
    connect(rows_le, &QLineEdit::textEdited, this, [this](){
        temp.rows = rows_le->text().toInt();
        CheckChanges();
        UpdateAdditionalData();
    });

    cols_le = new QLineEdit(this);
    cols_le->setValidator(side_validator);
    connect(cols_le, &QLineEdit::textEdited, this, [this](){
        temp.cols = cols_le->text().toInt();
        CheckChanges();
        UpdateAdditionalData();
    });

    size_lbl = new QLabel(this);

    mines_le = new QLineEdit(this);
    connect(mines_le, &QLineEdit::textEdited, this, [this](){
        temp.mines = mines_le->text().toInt();
        CheckChanges();
        UpdateMinesData();
    });

    mines_lbl = new QLabel(this);
}

void MinesweeperSetuper::SetupBtns()
{
    cancel_btn = new QPushButton("Cancel", this);
    cancel_btn->setDisabled(true);
    connect(cancel_btn, &QPushButton::clicked, this, [this]() {
        temp = *cur;
        SetCurrentData();
    });

    save_btn = new QPushButton("Save", this);
    save_btn->setDisabled(true);
    connect(save_btn, &QPushButton::clicked, this, [this](){
        bool is_size_changed = !cur->IsSameSize(temp);
        *cur = temp;
        (is_size_changed) ? emit SizeChanged() : emit MinesNumChanged();
    });
}

void MinesweeperSetuper::SetCurrentData()
{
    rows_le->setText(QString::number(cur->rows));
    cols_le->setText(QString::number(cur->cols));
    mines_le->setText(QString::number(cur->mines));

    UpdateAdditionalData();
}

void MinesweeperSetuper::UpdateAdditionalData()
{
    size_lbl->setText(QString("Cells: %1").arg(temp.GetCellsCounter()));
    UpdateMinesData();
}

void MinesweeperSetuper::UpdateMinesData()
{
    mines_lbl->setText(QString("Mines are %1% of all cells")
                           .arg(temp.GetMinesPercent()));

    mines_le->setStyleSheet(temp.AreMinesValid() ? valid_color : invalid_color);
    if (!temp.AreMinesValid()) {
        save_btn->setDisabled(true);
    }
}

void MinesweeperSetuper::CheckChanges()
{
    bool data_changed = !(*cur == temp);

    save_btn->setEnabled(data_changed);
    cancel_btn->setEnabled(data_changed);
}


//SETUPER------------------------------------------------------------------------------------------

Setuper::Setuper(MinesweeperSettings* minesweeper_settings,
                 QuizSettings* quiz_settings,
                 QWidget* parent)
    : QWidget(parent)
{
    setWindowTitle("Settings");

    QVBoxLayout* main_lay = new QVBoxLayout(this);

    QTabWidget* tab_w = new QTabWidget();

    minesweeper_setuper = new MinesweeperSetuper(minesweeper_settings, this);
    connect(minesweeper_setuper, &MinesweeperSetuper::SizeChanged, this, &Setuper::MinesweeperSizeChanged);
    connect(minesweeper_setuper, &MinesweeperSetuper::MinesNumChanged, this, &Setuper::MinesweeperMinesNumChanged);
    tab_w->addTab(minesweeper_setuper, "Minesweeper");

    QWidget* quiz_tab = new QWidget();
    tab_w->addTab(quiz_tab, "Quiz");

    main_lay->addWidget(tab_w);

    setFixedSize(minimumSize());
}

Setuper::~Setuper()
{
}
