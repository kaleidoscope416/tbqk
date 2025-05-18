#include "guanka.h"
#include "ui_guanka.h"
#include "level.h"

guanka::guanka(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::guanka)
{
    ui->setupUi(this);

}

guanka::~guanka()
{
    delete ui;
}

void guanka::on_level1_clicked()
{
    QString level1name = "D:/24489/Documents/untitled/question/level1.json";
    this->close();
    Level *level1 = new Level(level1name,4);
    delete this;
}


void guanka::on_level2_clicked()
{
    QString level2name = "D:/24489/Documents/untitled/question/level2.json";
    this->close();
    Level *level2 = new Level(level2name,4);
    delete this;
}


void guanka::on_level3_clicked()
{
    QString level3name = "D:/24489/Documents/untitled/question/level3.json";
    this->close();
    Level *level3 = new Level(level3name,4);
    delete this;
}

