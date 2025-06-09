#include "rank.h"

rank::rank() {
    this->widget = new QWidget;
    widget->setFixedSize(1600,900);
    QTableWidget *rank = new QTableWidget;
    loadRanking(rank,R_NAME);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(rank);

    QPushButton* backButton = new QPushButton("back", this->widget);
    connect(backButton, &QPushButton::clicked, this, [this](){
        MainWindow *newWindow = new MainWindow();
        newWindow->show();
        this->widget->close();
        disconnect(this, nullptr, nullptr, nullptr);
        this->deleteLater();
    });
    backButton->move(1200,50);
    backButton->show();
    QPushButton* deleteButton = new QPushButton("delete", this->widget);
    connect(deleteButton, &QPushButton::clicked, this, [this,rank](){
        deleteSelectedRow(rank,R_NAME);
    });
    deleteButton->move(1200,80);
    deleteButton->show();


    // 设置布局给widget
    widget->setLayout(layout);

    // 显示widget（rank会自动显示在widget里）
    widget->show();
}
