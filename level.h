#ifndef LEVEL_H
#define LEVEL_H

#include "mainwindow.h"
#include <QWidget>
#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QInputDialog>
#include "hexbotto.h"
#include <QElapsedTimer>
#include "record.h"


class Level : public QWidget
{
    Q_OBJECT
public:
    Level(QString name,int layer = 0,int mod = 0);
    HexagonButton* setButtonPosition(QWidget* widget = nullptr,int x=0, int y=0);
    void generateHexagonMap(int layers=0);
    bool is_neibor(HexagonButton* next_button);
    bool is_no_store(HexagonButton* cur_button);
    void store(HexagonButton* cur_button);
    void change_color(HexagonButton* cur_button);
    bool is_finish();
    void handle_click(HexagonButton* cur_button);
    void reset_page();
    void saveButtonStates(const QString& filename);
    int  loadButtonStates(const QString& filename);
    int loadButtonStatesLayers(const QString& filename);
    void handleClickButton(HexagonButton* button);
    virtual void getUserId(QWidget* parent = nullptr) ;
    void resultWindow(qint64 time);
    void saveScore();
    void resultScore();
    void back_to_main ();

public slots:


private:
    QWidget *widget;
    QList<QList<HexagonButton*>> button_map;
    QList<HexagonButton*> store_button_map;
    HexagonButton* last_button;
    QString question_name;
    QString playName;
    QString playerName;
    QElapsedTimer timer;
    int mod;
    qint64 use_time;
    int try_time = 0;
    int stride_length;
    int total_stride_length;
    double score;

    ~Level() {
    disconnect(this, nullptr, nullptr, nullptr);
        for (auto& row : button_map) {
            for (auto& button : row) {
                delete button;
            }
            row.clear();
        }
        button_map.clear();
        delete widget;

    }

    friend class Setmode;
};



#endif // LEVEL_H

