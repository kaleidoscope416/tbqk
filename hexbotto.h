#ifndef HEXBOTTO_H
#define HEXBOTTO_H

#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QRegion>

#define POSITIONX 640
#define POSITIONY 360

class HexagonButton : public QPushButton {
    Q_OBJECT

public:
    explicit HexagonButton(QWidget *parent = nullptr,int positionX = 0,int positionY = 0);
    int get_x() const;
    int get_y() const;
    bool get_color() const;
    void on_change_color();
    void on_change_color_v2();
    void resetbutton();
    void set_color(bool color);

    ~HexagonButton(){};
signals:
    void rightClicked();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override ;



private:
    int radius;
    QColor color;
    int x;
    int y;
    bool isPressed;
    bool mousePressed;
};

#endif
