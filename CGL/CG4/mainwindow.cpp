#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmath"

QImage img(400, 400, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ddaline(float x1, float y1, float x2, float y2)
{
    float x, y, dx, dy, xinc, yinc;
    int step;

    dx = x2 - x1;
    dy = y2 - y1;

    if(abs(dx) > abs(dy)){
        step = abs(dx);
    } else {
        step = abs(dy);
    }

    xinc = dx/step;
    yinc = dy/step;

    x = x1;
    y = y1;

    int i = 0;
    while( i <= step){
        img.setPixel(qRound(x), qRound(y), qRgb(255, 255, 255));
        x = x + xinc;
        y = y + yinc;
        i++;
    }

    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    ddaline(x1+200,y1+200,x2+200,y2+200);
    ddaline(x2+200,y2+200,x3+200,y3+200);
    ddaline(x3+200,y3+200,x1+200,y1+200);

    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_pushButton_clicked()
{
    ddaline(0, 200, 400, 200);
    ddaline(200, 0, 200, 400);
//    ddaline(200, 0, 200, 400);

}


void MainWindow::on_pushButton_2_clicked()
{

    x1 = ui->textEdit->toPlainText().toInt();
    y1 = ui->textEdit_2->toPlainText().toInt();
    x2 = ui->textEdit_3->toPlainText().toInt();
    y2 = ui->textEdit_4->toPlainText().toInt();
    x3 = ui->textEdit_5->toPlainText().toInt();
    y3 = ui->textEdit_6->toPlainText().toInt();
    drawTriangle(x1, y1, x2, y2, x3, y3);
}


void MainWindow::on_pushButton_3_clicked()
{
    float tx, ty;
    tx = ui->textEdit_7->toPlainText().toInt();
    ty = ui->textEdit_8->toPlainText().toInt();

    x1 = x1 + tx;
    y1 = y1 + ty;
    x2 = x2 + tx;
    y2 = y2 + ty;
    x3 = x3 + tx;
    y3 = y3 + ty;

    drawTriangle(x1, y1, x2, y2, x3, y3);
}


void MainWindow::on_pushButton_4_clicked()
{
    float sx, sy;
    sx = ui->textEdit_9->toPlainText().toInt();
    sy = ui->textEdit_10->toPlainText().toInt();

    x1 = x1 * sx;
    y1 = y1 * sy;
    x2 = x2 * sx;
    y2 = y2 * sy;
    x3 = x3 * sx;
    y3 = y3 * sy;

    drawTriangle(x1, y1, x2, y2, x3, y3);
}


void MainWindow::on_pushButton_5_clicked()
{
    float angle,required_angle;

    angle = ui->textEdit_11->toPlainText().toInt();
    required_angle = (angle * 0.0174533);

    x1 = x1 * cos(required_angle) - y1 * sin(required_angle);
    y1 = x1 * sin(required_angle) + y1 * cos(required_angle);
    x2 = x2 * cos(required_angle) - y2 * sin(required_angle);
    y2 = x2 * sin(required_angle) + y2 * cos(required_angle);
    x3 = x3 * cos(required_angle) - y3 * sin(required_angle);
    y3 = x3 * sin(required_angle) + y3 * cos(required_angle);

    drawTriangle(x1,y1,x2,y2,x3,y3);
}

