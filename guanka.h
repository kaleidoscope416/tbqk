#ifndef GUANKA_H
#define GUANKA_H

#include <QWidget>

namespace Ui {
class guanka;
}

class guanka : public QWidget
{
    Q_OBJECT

public:
    explicit guanka(QWidget *parent = nullptr);
    ~guanka();

private slots:
    void on_level1_clicked();

    void on_level2_clicked();

    void on_level3_clicked();

private:
    Ui::guanka *ui;
};

#endif // GUANKA_H
