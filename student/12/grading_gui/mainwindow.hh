#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <gradecounter.hh>

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

    //Get all necessary values
    void getValueN (int n);
    void getValueG (int g);
    void getValueP (int p);
    void getValueE (int e);

    void on_countPushButton_clicked();

private:
    Ui::MainWindow *ui;

    int valueN = 0;
    int valueG = 0;
    int valueP = 0;
    int valueE = 0;

};
#endif // MAINWINDOW_HH
