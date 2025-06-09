#ifndef RECORD_H
#define RECORD_H
#define R_NAME "record.csv"

#include <QTableWidget>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QVector>
#include <QMessageBox>
#include <algorithm>

class Record {
public:
    QString playerName;
    QString questionName;
    QString playName;
    double score;


    bool compareScore(const Record &other) const;
};

void loadRanking(QTableWidget *table, const QString &filename);
void deleteSelectedRow(QTableWidget *table, const QString &filename);




#endif // RECORD_H
