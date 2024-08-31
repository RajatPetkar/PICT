#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_pushButton_clicked();
    int signfn(float,float);
    void dda(float, float, float, float);
    void Bresenham_circle(float, float, float);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
