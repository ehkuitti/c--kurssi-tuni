#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Includetaan tavaraa sekä standardikirjastosta että QT:n puolelta

#include "gameboard.hh"

#include <QFile>
#include <QDebug>
#include <QGraphicsView>
#include <QGridLayout>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>
#include <iostream>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // Go to slotilla autogeneroidut funktiot
    void on_horizontalSlider_sliderMoved(int position);
    void on_newGamePushButton_clicked();
    void on_seedValueSpinBox_valueChanged(int arg1);
    void on_setFlagCheckBox_stateChanged(int arg1);

    // Omat apufunktiot, jotka toimivat slottien tapaan
    void handleSquareClicks();
    void onSecTimer();
    void initButtons();

private:

    // Nappia koskevat arvot kovakoodataan vakioiksi
    const int BUTTON_SIZE = 50;
    const int MARGIN_SIZE = 100;

    // Selvittää, onko setFlagCheckBox rastitettu (oletuksena ei ole eli false)
    bool isFlagActive_ = false;
    int seedValue_ = 0;

    // Standardikirjastoa hyödyntävät muuttujat
    std::vector<std::vector<QPushButton*>> graphicalBoard_  = {};
    std::shared_ptr<GameBoard> board_ = {};

    // QT:ta hyödyntävät muuttujat
    QTimer* timer_;
    Ui::MainWindow *ui;

    // Laudan koko alustetaan nollalla
    int boardSize_ = 0;

    // Omia apufunktioita
    void openSquare(unsigned x, unsigned y);
    void gameOver(bool isGameWon = false);
    void addButtonIcon(QPushButton* button, QString path);
    void clearBoard();
    QString formFileName(int adjacent);

};
#endif // MAINWINDOW_H
