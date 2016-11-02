#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <math.h>
#include <fstream>
#include <iostream>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scaleX->setText("1");
    ui->scaleY->setText("1");
    ui->rotateAngle->setText("0");
    ui->rotateX->setText("0");
    ui->rotateY->setText("0");
    ui->translateX->setText("0");
    ui->translateY->setText("0");
    ui->imageNumber->setText("1");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_released()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Images (*.png *.xpm *.jpg)"));
    ui->imagePath->setText(fileName);
    imageProcessing.openImage(fileName.toStdString());
}

void MainWindow::on_scaleX_editingFinished()
{
    if (0.0 - ui->scaleX->text().toDouble() >= 0)
        ui->scaleX->setText("1");
}

void MainWindow::on_scaleY_editingFinished()
{
    if (0.0 - ui->scaleY->text().toDouble() >= 0)
        ui->scaleY->setText("1");
}

void MainWindow::on_n_editingFinished()
{
    if (0.0 - ui->n->text().toDouble() >= 0)
        ui->n->setText("1");
}

void MainWindow::on_apply_released()
{
    imageProcessing.transform(ui->imageNumber->text().toInt() - 1, ui->scaleX->text().toDouble(), ui->scaleY->text().toDouble(), ui->rotateAngle->text().toDouble(), ui->rotateX->text().toDouble(), ui->rotateY->text().toDouble(), ui->translateX->text().toDouble(), ui->translateY->text().toDouble(), ui->histogramEqualization->isChecked(), ui->negative->isChecked(), ui->log->isChecked(), ui->inverseLog->isChecked(), ui->nthPower->isChecked(), ui->n->text().toDouble());
}

void MainWindow::on_imageNumber_editingFinished()
{
    if (ui->imageNumber->text().toInt() < 1 || ui->imageNumber->text().toInt() > imageProcessing.getNumberOfImages())
        ui->imageNumber->setText("1");
}
