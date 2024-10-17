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
    void dda(float x1, float y1, float x2, float y2);
    void drawCurve(int it, int x1, int y1, int x2, int y2);

    void drawSnowflake(int it, int x1, int y1, int x2, int y2, int x3, int y3);
private slots:
    void on_create_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
