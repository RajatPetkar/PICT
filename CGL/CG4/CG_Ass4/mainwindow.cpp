#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
QImage image(400,400,QImage::Format_RGB888);

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
    ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::on_pushButton_clicked()
{
    dda(0,200,400,200);
    dda(200,0,200,400);
}


void MainWindow::on_pushButton_2_clicked()
{
    float term1,term_x,x,x1,y1,y,R,x2,y2,x3,y3;

    //To get the centre of the triangle
    x1 = ui->textEdit->toPlainText().toFloat();
    y1 = ui->textEdit_2->toPlainText().toFloat();

    //To draw the Triangle
    R = ui->textEdit_3->toPlainText().toFloat();
    x=x1+200;
    y=200-y1;
    x2 = (x + R);
    y2=y;
    x3=(x+(R/2));
    term_x=(x3-x);
    term1=pow(R,2)-pow(term_x,2);
    y3=y-sqrt(term1);
    dda(x,y,x2,y2);
    dda(x2,y2,x3,y3);
    dda(x,y,x3,y3);
}

float MainWindow::matMul(float arr1[2][3],float arr2[3][3])
{
    float res[2][3];
    int i,j,k;
    for (int i = 0; i <2; i++)
    {
        for (int j = 0; j <3; j++)
        {
                    for (int k = 0; j <3; k++)
                    {
                        res[i][j]=res[i][j]+(arr1[i][k]*arr2[k][j]);
                    }
        }

    }
    return res[2][3];
}



//DONT TOUCH THIS IDIOT BELOW
void MainWindow::on_label_linkActivated(const QString &link)
{

}

void MainWindow::on_pushButton_3_clicked()
{
    float term1,term_x,x,x1,transX,transY,y,y1,R,x2,y2,x3,y3;
    transX = ui->textEdit_4->toPlainText().toFloat();
    transY = ui->textEdit_5->toPlainText().toFloat();
    x1 = ui->textEdit->toPlainText().toFloat();
    y1 = ui->textEdit_2->toPlainText().toFloat();

    //To draw the Triangle
    R = ui->textEdit_3->toPlainText().toFloat();
    x=x1+200+transX;
    y=200-y1-transY;
    x2 = (x + R);
    y2=y;
    x3=(x+(R/2));
    term_x=(x3-x);
    term1=pow(R,2)-pow(term_x,2);
    y3=y-sqrt(term1);
    dda(x,y,x2,y2);
    dda(x2,y2,x3,y3);
    dda(x,y,x3,y3);

}

void MainWindow::on_pushButton_4_clicked()
{
    float x,x1,transX,transY,y,y1,rotat_deg,rotat_rad,x2,y2,x3,y3,term_x,term1,L,sin_half;
    int newPoint;
    transX = ui->textEdit_4->toPlainText().toFloat();
    transY = ui->textEdit_5->toPlainText().toFloat();
    x1 = ui->textEdit->toPlainText().toFloat();
    y1 = ui->textEdit_2->toPlainText().toFloat();
    L=ui->textEdit_3->toPlainText().toFloat();
    rotat_deg = ui->textEdit_6->toPlainText().toFloat();
    rotat_rad= rotat_deg*(3.14/180);
    sin_half=sin(rotat_rad);
    newPoint=2*L*sin_half;

    x=x1+200;
    y=200-y1;
    x2 = (x + L)-newPoint;
    y2=y-newPoint;
    x3=(x+(L/2))-newPoint;
    term_x=(x3-x);
    term1=pow(L,2)-pow(term_x,2);
    y3=y-sqrt(term1)-newPoint;

    dda(x,y,x2,y2);
    dda(x2,y2,x3,y3);
    dda(x,y,x3,y3);
    dda(x,y,x2,y2);
    dda(x2,y2,x3,y3);
    dda(x,y,x3,y3);

}
