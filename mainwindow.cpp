#include "mainwindow.h"

#include <QLayout>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("~~Minesweeper~~");

    SetupQuiz();

    SetupMsgBoxes();
    SetupSetuper();

    QWidget* main_w = new QWidget(this);
    QVBoxLayout* main_lay = new QVBoxLayout(main_w);

    QWidget* TEST_w = new QWidget(this);
    QHBoxLayout* TEST_lay = new QHBoxLayout(TEST_w);
    TEST_lay->addWidget(TEST_quiz_btn);
    main_lay->addWidget(TEST_w);

    QWidget* ui_w = new QWidget(this);
    QGridLayout* ui_lay = new QGridLayout(ui_w);
    ui_lay->setHorizontalSpacing(10);
    ui_lay->setVerticalSpacing(5);
    SetupUI();
    ui_lay->addWidget(stats, 0, 0, 4, 1, Qt::AlignRight);
    ui_lay->addWidget(reset_btn, 1, 1, Qt::AlignLeft);
    ui_lay->addWidget(setuper_btn, 2, 1, Qt::AlignLeft);
    main_lay->addWidget(ui_w);

    SetupField();
    main_lay->addWidget(field, 0, Qt::AlignHCenter);

    setCentralWidget(main_w);
    //setFixedSize(minimumSize());
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

MainWindow::~MainWindow()
{
    if (setuper != nullptr) delete setuper;
    setuper = nullptr;

    if (TEST_quiz != nullptr) delete TEST_quiz;
    TEST_quiz = nullptr;
}

void MainWindow::SetupQuiz()
{
    TEST_quiz_btn = new QPushButton("Try Quiz", this);
    TEST_quiz = new Quiz();
    connect(TEST_quiz_btn, &QPushButton::clicked, TEST_quiz, &Quiz::show);
}

void MainWindow::SetupMsgBoxes()
{
    loose_game_msgbox = new GameEndMsgBox("GameOver", "FIeld is boomed.", "Try again", "Sorry");
    connect(loose_game_msgbox, &GameEndMsgBox::AgainClicked, this, &MainWindow::ResetField);
    connect(loose_game_msgbox, &GameEndMsgBox::ContinueClicked, this, &MainWindow::ForgiveMistake);

    win_game_msgbox = new GameEndMsgBox("Win", "You are such a beauty!\nGeronimo!", "Try again", "Get rest");
    connect(win_game_msgbox, &GameEndMsgBox::AgainClicked, this, &MainWindow::ResetField);
    connect(win_game_msgbox, &GameEndMsgBox::ContinueClicked, win_game_msgbox, &GameEndMsgBox::close);
}

void MainWindow::SetupSetuper()
{
    setuper = new Setuper(&settings);
    connect(setuper, &Setuper::FieldSizeChanged, this, &MainWindow::RebuildField);
    connect(setuper, &Setuper::FieldDetailsChanged, this, &MainWindow::ResetField);
}

void MainWindow::SetupUI()
{
    stats = new StatData(this);
    stats->Reset(settings.mines);

    reset_btn = new QPushButton("Reset", this);
    connect(reset_btn, &QPushButton::clicked, this, &MainWindow::ResetField);

    setuper_btn = new QPushButton("Settings", this);
    connect(setuper_btn, &QPushButton::clicked, setuper, &Setuper::show);
}

void MainWindow::SetupField()
{
    field = new FieldView(settings.rows, settings.cols, settings.mines, this);

    connect(field, &FieldView::FieldIsCompleted, win_game_msgbox, &GameEndMsgBox::exec);
    connect(field, &FieldView::FieldIsBoomed, loose_game_msgbox, &GameEndMsgBox::exec);

    connect(field, &FieldView::MarksCounterChanged, stats, &StatData::UpdateMinesData);
    connect(field, &FieldView::Clicked, stats, &StatData::AddClick);
}

void MainWindow::RebuildField()
{
    if (field != nullptr) {
        centralWidget()->layout()->takeAt(1)->invalidate();
        delete field;
    }
    SetupField();

    QWidget* field_w = new QWidget(this);
    QVBoxLayout* field_lay = new QVBoxLayout(field_w);
    field_lay->addWidget(field, 0, Qt::AlignHCenter);
    centralWidget()->layout()->addWidget(field_w);

    stats->Reset(settings.mines);
}

void MainWindow::ResetField()
{
    field->Reset(settings.mines);
    stats->Reset(settings.mines);
}

void MainWindow::ForgiveMistake()
{
    field->HideMine();
    stats->AddMistake();
}
