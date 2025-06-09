#ifndef RANK_H
#define RANK_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "mainwindow.h"
#include "record.h"

class rank : public QWidget
{
    Q_OBJECT
public:
    rank();

private:
    QWidget* widget;

};

#endif // RANK_H
