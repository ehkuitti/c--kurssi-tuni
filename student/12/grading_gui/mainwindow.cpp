#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->spinBoxN, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::getValueN);
    connect(ui->spinBoxG, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::getValueG);
    connect(ui->spinBoxP, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::getValueP);
    connect(ui->spinBoxE, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::getValueE);
    connect(ui->countPushButton, &QPushButton::clicked, this, &MainWindow::on_countPushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getValueN(int n)
{
    valueN = n;
}

void MainWindow::getValueG(int g)
{
    valueG = g;
}

void MainWindow::getValueP(int p)
{
    valueP = p;
}

void MainWindow::getValueE(int e)
{
    valueE = e;
}

void MainWindow::on_countPushButton_clicked()
{
    int finalGrade = count_final_grade(valueN, valueG, valueP, valueE);
    QString finalStringGrade = QString::number(finalGrade);
    ui->textBrowser->setText("Total grade: " + finalStringGrade);
//    std::cout << "Total grade: " << finalGrade;
}

//void MainWindow::getValueN(unsigned& n)
//{
////    int nArvo = n;
//}

//void MainWindow::getValueG(unsigned &g)
//{

//}

//void MainWindow::getValueP(unsigned &p)
//{

//}

//void MainWindow::getValueE(unsigned &e)
//{

//}

