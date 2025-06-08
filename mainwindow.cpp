#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QTabWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "guanka.h"
#include "setmode.h"

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




void MainWindow::on_levelmode_clicked()
{
    guanka *guankapage = new guanka();
    this->close();
    guankapage->show();
}

void MainWindow::on_pushButton_clicked()
{

    Setmode* setmodepage = new Setmode();
    this->close();
    //setmodepage -> show();
}


void MainWindow::on_pushButton_2_clicked()
{
    // bool ok;
    // int layers = QInputDialog::getInt(this, "Input Dialog", "Enter number of layers:", 4, 1, 10, 1, &ok);
    // if (!ok) {
    //     layers = 4;
    // }
     QString levelname = QFileDialog::getOpenFileName(this, "Open 关卡", "", "JSON Files (*.json)");
    if (levelname.isEmpty()) {
         return;
    }
    Level *level = new Level(levelname,2);
    this->close();
}

