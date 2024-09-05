#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<QPainter>
#include<QImage>
#include<QColorDialog>
#include<QMouseEvent>
#include<math.h>
#include<cmath>
#include<QTime>
using namespace std;
QImage img(500,500,QImage::Format_RGB888);
QColor color=qRgb(255,255,255);
QColor c1,c2;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     start=true;
     count=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
 c1 = QColorDialog::getColor();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(start){
        int p = event->pos().x();
        int q = event->pos().y();
        a[count]=p;
        b[count]=q;
        if(event->button()==Qt::RightButton){
            line(a[0],b[0],a[count-1],b[count-1]);
//            line(a[count-1]+1,b[count-1]+1,a[0]+1,b[0]+1);
            start=false;
//            cout<<"final"<<endl;
        }
        else{
            if(count>0){
                line(a[count],b[count],a[count-1],b[count-1]);
//                line(a[count]+1,b[count]+1,a[count-1]+1,b[count-1]+1);
            }
            count++;
        }
    }
    ui->label->setPixmap((QPixmap::fromImage(img)));
}

void MainWindow::line(int x1, int y1, int x2, int y2)
{
//    float dx ,dy,steps,xinc,yinc;
//    int x,y;

//    dx=x2-x1;
//    dy=y2-y1;

//    steps = dy;
//    if(abs(dx)>abs(dy)){
//           steps = abs(dx);
//    }else{
//   steps=abs(dy);
//    xinc = dx/steps;
//    yinc = dy/steps;

//    x = x1;
//    y = y1;
//    int i = 0;
//    while(i<steps){
//        img.setPixel(x,y,qRgb(0,255,0));
//        x = x + xinc;
//        y = y + yinc;
//        i++;QColor c1,c2;

//       }
//     ui->label->setPixmap((QPixmap::fromImage(img)));
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = float(dx) / float(steps);
    float yIncrement = float(dy) / float(steps);

    float x = x1;
    float y = y1;

    img.setPixel(round(x), round(y),c1.rgb());

    for (int i = 1; i <= steps; i++) {
        x += xIncrement;
        y += yIncrement;
        img.setPixel(round(x), round(y),c1.rgb());
    }
    ui->label->setPixmap((QPixmap::fromImage(img)));
//    float step;
//    float dx = x2-x1;
//    float dy = y2-y1;
//    if (abs(dx) >= abs(dy) )
//        step = abs(dx);
//    else
//        step = abs(dy);
//    float x=x1;float y=y1; float i=0;
//    float xine = dx/step ; float yine = dy/step;
//    while (i <= step){
//        x=x+xine;
//        y=y+yine;
//        img.setPixel(x,y,c1.rgb());
//        i++;
//    }
//    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_2_clicked()
{
    a[count] = a[0];
    b[count] = b[0];
    for (int i = 0; i < count; i++) {
        float dy = b[i + 1] - b[i];
        float dx = a[i + 1] - a[i];
        if (dy == 0.0f) {
            slope[i] = 1.0;
        }if (dx == 0.0f) {
            slope[i] = 0.0;
        } if(dy!=0.0f && dx!=0.0f) {
            slope[i] = dx / dy;
        }
    }
    for (int y = 0; y < 431; y++) {
        int k = 0;
        for (int i = 0; i < count; i++) {
            if (((b[i] <= y) && (b[i + 1] > y)) || ((b[i] > y) && (b[i + 1] <= y))) {
                xi[k] = int(a[i] + slope[i] * (y - b[i]));
                k++;
            }
        }
        for (int j = 0; j < k - 1; j++) {
            for (int i = 0; i < k - j - 1; i++) {
                if (xi[i] > xi[i + 1]) {
                    int temp = xi[i];
                    xi[i] = xi[i + 1];
                    xi[i + 1] = temp;
                }
            }
        }
        for (int i = 0; i < k; i += 2) {
            if (i + 1 < k) {
                line(xi[i], y, xi[i + 1], y);
            }
        }
}
}
