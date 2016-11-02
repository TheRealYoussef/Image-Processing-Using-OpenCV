#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imageprocessing.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ImageProcessing imageProcessing;

private slots:
    void on_pushButton_released();
    void on_scaleX_editingFinished();
    void on_scaleY_editingFinished();
    void on_n_editingFinished();
    void on_apply_released();
    void on_imageNumber_editingFinished();
};

#endif // MAINWINDOW_H
