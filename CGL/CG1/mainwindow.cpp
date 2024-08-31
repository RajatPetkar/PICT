#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
QImage image(400,501,QImage::Format_RGB888);

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

int MainWindow::signfn(float coor1, float coor2)
{
    float sign;
    if(coor1 < coor2)
    {
        sign = 1;
    }
    else
    {
        sign = -1;
    }
    return sign;
}


void MainWindow::on_pushButton_clicked()
{
    float x,y,R,r,x1,a,y1,x2,y2,x3,y3;
    x = ui->textEdit->toPlainText().toFloat();
    y = ui->textEdit_2->toPlainText().toFloat();
    R = ui->textEdit_3->toPlainText().toFloat();
    r = R/2.0;
    a = sqrt(3)/2.0;
    x1 = x;
    x2 = (x - (a*R));
    y1 = y - R;
    y2 = y + r;
    x3 = ((a*R) + x);
    y3 = y2;
    dda(x2,y2,x1,y1);
    dda(x1,y1,x3,y3);
    dda(x3,y3,x2,y2);


}

void MainWindow::dda(float x1,float y1, float x2, float y2)
{
    float dx,dy,length,xinc,yinc,x,y,k;
    float sign1,sign2;
    dx = x2-x1;
    dy = y2-y1;
    if(abs(dx)>abs(dy))
    {
        length = abs(dx);
    }
    else
    {
        length = abs(dy);
    }
    xinc = dx/length;
    yinc = dy/length;

    sign1 = signfn(x1, x2);
    sign2 = signfn(y1, y2);

    x = x1 + (0.5*sign1);
    y = y1 + (0.5*sign2);
    k = 1;
    while(k <= length)
    {
        x = x + xinc;
        y = y + yinc;
        image.setPixel(x,y,qRgb(255,255,255));
        k = k + 1;
    }
    ui->label_5->setPixmap(QPixmap::fromImage(image));

}


void MainWindow::Bresenham_circle(float xc, float yc, float R)
{
    int x,y,d;
    x = 0;
    y = R;
    d = 3 - (2*R);
    QRgb color;
    color = qRgb(255,255,255);
    while(y >= x)
    {
        image.setPixel(x+xc, y+yc, color);
        image.setPixel(-x+xc, y+yc, color);
        image.setPixel(x+xc, -y+yc, color);
        image.setPixel(-x+xc, -y+yc, color);
        image.setPixel(y+xc, x+yc, color);
        image.setPixel(-y+xc, x+yc, color);
        image.setPixel(y+xc, -x+yc, color);
        image.setPixel(-y+xc, -x+yc, color);

        x++;
        if(d > 0)
        {
            y--;
            d = d + (4*(x-y)) + 10;
        }
        else
        {
            d = d + (4*x) + 6;
        }

    }
    ui->label_5->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_2_clicked()
{
    float x,y,R,r;
    x = ui->textEdit->toPlainText().toFloat();
    y = ui->textEdit_2->toPlainText().toFloat();
    R = ui->textEdit_3->toPlainText().toFloat();
    r = R/2;
    Bresenham_circle(x, y, R);
    Bresenham_circle(x, y, r);
}

void MainWindow::on_pushButton_3_clicked()
{

}
