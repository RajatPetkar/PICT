#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

QImage img(600, 600, QImage::Format_RGB888);
QColor bgColor(qRgb(0,0,0));
QColor color(qRgb(230, 230, 230));

int it=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img.fill(bgColor);
        ui->display->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::dda(float x1,float y1,float x2,float y2){
    int length = 0;
    if (abs(x2 - x1) >= abs(y2 - y1)){
        length = abs(x2 - x1);
    }
    else {
        length = abs(y2 - y1);
    }
    float dx = float(x2 - x1)/float(length);
    float dy = float(y2 - y1)/float(length);
    float x = x1;
    float y = y1;
    int i = 1;
    while (i <= length){
        img.setPixelColor(x, y, color);
        x = x + dx;
        y = y + dy;
        i++;
    }
    ui->display->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::drawCurve(int it, int x1, int y1, int x2, int y2)
{
    //base case
    if(it == 0){
        dda(x1, y1, x2, y2);
    }

    else{
        //draw curve
        int x3 = (2*x1 + x2)/3;
        int y3 = (2*y1 + y2)/3;

        int x4 = (x1 + 2*x2)/3;
        int y4 = (y1 + 2*y2)/3;

        int x5 = x3 + (x4 - x3)*(0.5) + (y4 - y3)*(0.86);
        int y5 = y3 - (x4 - x3)*(0.86) + (y4 - y3)*(0.5);

        drawCurve(it-1, x1, y1, x3, y3);
        drawCurve(it-1, x3, y3, x5, y5);
        drawCurve(it-1, x5, y5, x4, y4);
        drawCurve(it-1, x4, y4, x2, y2);
    }

}
void MainWindow::drawSnowflake(int it, int x1, int y1, int x2, int y2, int x3, int y3)
{
    // Draw Koch curves on each side of the triangle
    drawCurve(it, x1, y1, x2, y2);
    drawCurve(it, x2, y2, x3, y3);
    drawCurve(it, x3, y3, x1, y1);
}

void MainWindow::on_create_clicked()
{
    img.fill(bgColor);
    ui->display->setPixmap(QPixmap::fromImage(img));

    it = ui->level->toPlainText().toInt();
//    drawCurve(it, 100, 250, 400, 250);
    drawSnowflake(it, 300, 100, 500, 100, 400, 300);

}

MainWindow::~MainWindow()
{
    delete ui;
}

