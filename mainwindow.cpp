#include "mainwindow.h"

#include <QLayout>


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("~~Minesweeper~~");

    SetupMsgBoxes();
    SetupSetuper();

    QGridLayout* ui_lay = new QGridLayout();
    ui_lay->setHorizontalSpacing(10);
    ui_lay->setVerticalSpacing(5);

    SetupUI();
    ui_lay->addWidget(stats, 0, 0, 4, 1, Qt::AlignRight);
    ui_lay->addWidget(reset_btn, 1, 1, Qt::AlignLeft);
    ui_lay->addWidget(setuper_btn, 2, 1, Qt::AlignLeft);

    QVBoxLayout* main_lay = new QVBoxLayout();
    main_lay->addLayout(ui_lay);
    SetupField();
    main_lay->addWidget(field, 0, Qt::AlignHCenter);

    QWidget* w = new QWidget();
    w->setLayout(main_lay);
    setCentralWidget(w);

    //setFixedSize(minimumSize());
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void MainWindow::SetupMsgBoxes()
{
    looser_msgbox = new QMessageBox();
    looser_msgbox->setWindowTitle("GameOver");
    looser_msgbox->setText("FIeld is boomed");

    again_for_loosers_btn = new QPushButton("Again");
    looser_msgbox->addButton(again_for_loosers_btn, QMessageBox::ActionRole);
    sorry_btn = new QPushButton("Sorry");
    looser_msgbox->addButton(sorry_btn, QMessageBox::ActionRole);

    winner_msgbox = new QMessageBox();
    winner_msgbox->setWindowTitle("Win!");
    winner_msgbox->setText("You are such a beauty!\nGeronimo!");

    again_for_winners_btn = new QPushButton("One more");
    winner_msgbox->addButton(again_for_winners_btn, QMessageBox::ActionRole);
    super_btn = new QPushButton("Get rest");
    winner_msgbox->addButton(super_btn, QMessageBox::ActionRole);
}

void MainWindow::SetupSetuper()
{
    setuper = new Setuper(&settings);
    connect(setuper, &Setuper::FieldSizeChanged, this, &MainWindow::RebuildField);
    connect(setuper, &Setuper::FieldDetailsChanged, this, &MainWindow::ResetField);
}

void MainWindow::SetupUI()
{
    stats = new StatData();
    stats->Reset(settings.mines);

    reset_btn = new QPushButton("Reset");
    connect(reset_btn, &QPushButton::clicked, this, &MainWindow::ResetField);

    setuper_btn = new QPushButton("Settings");
    connect(setuper_btn, &QPushButton::clicked, setuper, &Setuper::show);
}

void MainWindow::SetupField()
{
    field = new FieldView(settings.rows, settings.cols, settings.mines);

    connect(field, &FieldView::FieldIsCompleted, this, &MainWindow::Win);
    connect(field, &FieldView::FieldIsBoomed, this, &MainWindow::GameOver);

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

    QVBoxLayout* field_lay = new QVBoxLayout();
    field_lay->addWidget(field, 0, Qt::AlignHCenter);

    QWidget* field_w = new QWidget();
    field_w->setLayout(field_lay);
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

void MainWindow::GameOver()
{
    looser_msgbox->exec();
    if (looser_msgbox->clickedButton() == again_for_loosers_btn) {
        ResetField();
    }
    if (looser_msgbox->clickedButton() == sorry_btn) {
        ForgiveMistake();
    }
}

void MainWindow::Win()
{
    winner_msgbox->exec();
    if (winner_msgbox->clickedButton() == again_for_winners_btn) {
        ResetField();
    }
    if (winner_msgbox->clickedButton() == super_btn) {
        winner_msgbox->close();
    }
}
