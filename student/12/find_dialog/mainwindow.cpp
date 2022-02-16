#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QStringMatcher>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_findPushButton_clicked()
{

    QFile file_reader(ui->fileLineEdit->text());
    file_reader.open(QIODevice::ReadOnly);
    QString parsable_file_line;
    QTextStream file_stream (&file_reader);
    QString user_input = ui->keyLineEdit->text();
    bool wordFound = false;

    if (ui->matchCheckBox->isChecked())
    {
        if (!file_reader.exists())
        {
            ui->textBrowser->setText("File not found");
        }

        else if (user_input.length() <= 0)
        {
            ui->textBrowser->setText("File found");
        }

        else if ((user_input.length() > 0) && (file_reader.exists()))
        {
            while (file_stream.readLineInto(&parsable_file_line))
            {
    //            std::cout << parsable_file_line.toStdString() << std::endl;
                if (parsable_file_line == user_input)
                {
                    ui->textBrowser->setText("Word found\n");
                    wordFound = true;
                    break;
                }

                else
                {
                    continue;
                }
            }

            if (wordFound != true)
            {
                ui->textBrowser->setText("Word not found");
            }
        }
    }

    else //Jos case-sensitiiviydellä ei ole väliä
    {
        if (!file_reader.exists())
        {
            ui->textBrowser->setText("File not found");
        }

        else if (user_input.length() <= 0)
        {
            ui->textBrowser->setText("File found");
        }

        else if ((user_input.length() > 0) && (file_reader.exists()))
        {
            while (file_stream.readLineInto(&parsable_file_line))
            {
    //            std::cout << parsable_file_line.toStdString() << std::endl;
                if (parsable_file_line.SectionCaseInsensitiveSeps == user_input.SectionCaseInsensitiveSeps)
                {
                    ui->textBrowser->setText("Word found");
                    wordFound = true;
                    break;
                }

                else
                {
                    continue;
                }
            }

            if (wordFound != true)
            {
                ui->textBrowser->setText("Word not found");
            }
        }
    }
}
