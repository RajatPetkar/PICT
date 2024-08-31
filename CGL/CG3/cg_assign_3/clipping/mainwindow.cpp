#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

QImage image(300, 300, QImage::Format_RGB888);
QImage image2(300, 300, QImage::Format_RGB888);
static QColor color,color2;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::dda(float x1, float y1, float x2, float y2)
{
    float dy = y2 - y1;
    float dx = x2 - x1;
    float len = abs(dx);
    if (abs(dy) > abs(dx))
    {
        len = abs(dy);
    }
    float x = x1;
    float y = y1;
    float xinc = dx / len;
    float yinc = dy / len;
    for (int i = 0; i <= len; i++)
    {
        x = x + xinc;
        y = y + yinc;
        image.setPixel(x, y, qRgb(255,255,255));
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::dda2(float x1, float y1, float x2, float y2)
{
    float dy = y2 - y1;
    float dx = x2 - x1;
    float len = abs(dx);
    if (abs(dy) > abs(dx))
    {
        len = abs(dy);
    }
    float x = x1;
    float y = y1;
    float xinc = dx / len;
    float yinc = dy / len;
    for (int i = 0; i <= len; i++)
    {
        x = x + xinc;
        y = y + yinc;
        image2.setPixel(x, y, qRgb(255,255,255));
    }
    ui->label_2->setPixmap(QPixmap::fromImage(image2));
}
void MainWindow::window()
{
    dda(xmin, ymin, xmax, ymin);
    dda(xmax, ymin, xmax, ymax);
    dda(xmax, ymax, xmin, ymax);
    dda(xmin, ymax, xmin, ymin);
}
void MainWindow::window1()
{
    dda2(xmin, ymin, xmax, ymin);
    dda2(xmax, ymin, xmax, ymax);
    dda2(xmax, ymax, xmin, ymax);
    dda2(xmin, ymax, xmin, ymin);
}

void MainWindow::on_pushButton_clicked()
{
    window();
    float x1, y1, x2, y2;
    x1 = ui->textEdit->toPlainText().toFloat();
    y1 = ui->textEdit_2->toPlainText().toFloat();
    x2 = ui->textEdit_3->toPlainText().toFloat();
    y2 = ui->textEdit_4->toPlainText().toFloat();
    dda(x1, y1, x2, y2);
    ui->label->setPixmap(QPixmap::fromImage(image));
}
int MainWindow::regioncode(double x, double y)
{
    int code=0;

    if(x<xmin){
        code=code|Left;
    }
    if(x>xmax){
        code=code|Right;
    }
    if(y<ymin){
        code=code|Bot;
    }
    if(y>ymax){
        code=code|Top;
    }

    return code;

}

bool MainWindow::clipping(double &x1, double &y1, double &x2, double &y2)
{
    int code;
    double x,y;


    while(true){
        if(code1==0 && code2==0){
            return true;
        }
        else if(code1&code2){
            return false;

        }
        if(code1!=0){
            code=code1;
        }
        else{
            code=code2;
        }
        if(code&Top){
            x=x1+(x2-x1)*(ymax-y1)/(y2-y1);
            y=ymax;

        }
        if(code&Bot){
            x=x1+(x2-x1)*(ymin-y1)/(y2-y1);
            y=ymin;
        }
        if(code&Right){
            y=y1+(y2-y1)*(xmax-x1)/(x2-x1);
            x=xmax;
        }
        if(code&Left){
            y=y1+(y2-y1)*(xmin-x1)/(x2-x1);
            x=xmin;
        }
        if(code==code1){
            x1=x;
            y1=y;
            code1=regioncode(x1,y1);
        }
        else{
            x2=x;
            y2=y;
            code2=regioncode(x2,y2);
        }
    }


}

void MainWindow::on_pushButton_2_clicked()
{
    window1();
    x1=ui->textEdit->toPlainText().toInt();
    y1=ui->textEdit_2->toPlainText().toInt();
    x2=ui->textEdit_3->toPlainText().toInt();
    y2=ui->textEdit_4->toPlainText().toInt();

    code1=regioncode(x1,y1);
    code2=regioncode(x2,y2);

    bool accept=clipping(x1,y1,x2,y2);

    if(accept){
        dda2(x1,y1,x2,y2);
        ui->label_2->setPixmap(QPixmap::fromImage(image2));
    }
}


