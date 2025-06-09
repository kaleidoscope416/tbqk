#include "rank.h"

bool Record::compareScore(const Record &other) const {
    return this->score > other.score;
}

void loadRanking(QTableWidget *table, const QString &filename) {
    QVector<Record> records;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() <<"文件打开失败", "无法打开排行榜文件: " ;
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() == 4) {
            Record rec;
            rec.playerName = parts[0];
            QString name = parts[1].section('/', -1, -1);
            name.remove(".json");
            rec.questionName = name;
            rec.score = parts[2].toDouble();
            rec.playName = parts[3];
            records.append(rec);
        }
    }
    file.close();

    std::sort(records.begin(), records.end(), [](const Record &a, const Record &b) { return a.compareScore(b); });

    table->setRowCount(records.size());
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "排名" << "玩家名" << "题目名" << "分数"<<"命题人");

    for (int i = 0; i < records.size(); ++i) {
        table->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        table->setItem(i, 1, new QTableWidgetItem(records[i].playerName));
        table->setItem(i, 2, new QTableWidgetItem(records[i].questionName));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(records[i].score)));
        table->setItem(i, 4, new QTableWidgetItem(records[i].playName));
    }
}

void deleteSelectedRow(QTableWidget *table, const QString &filename) {
    int row = table->currentRow();
    if (row < 0) {
        QMessageBox::warning(table, "提示", "请先选中要删除的行！");
        return;
    }

    // 读取所有数据
    QVector<Record> records;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 4) {
                Record rec;
                rec.playerName = parts[0];
                rec.questionName = parts[1];
                rec.score = parts[2].toDouble();
                rec.playName = parts[3];
                records.append(rec);
            }
        }
        file.close();
    }

    // 删除选中行对应的数据
    if (row < records.size()) {
        records.removeAt(row);
    }

    // 重新写回文件
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&file);
        for (const Record &rec : records) {
            out << rec.playerName << "," << rec.questionName << "," << rec.score << "," << rec.playName << "\n";
        }
        file.close();
    }

    // 刷新表格
    loadRanking(table, filename);
}
