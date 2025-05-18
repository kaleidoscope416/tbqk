#include "hexbotto.h"

HexagonButton::HexagonButton(QWidget *parent , int positionX , int positionY)
    : QPushButton(parent), radius(30), color(Qt::white) ,x(0),y(0),isPressed(false){
    setFixedSize(2 * radius, 2 * radius);
    this -> move(POSITIONX+positionX,POSITIONY+positionY);
    x = positionX;
    y = positionY;
}

int HexagonButton::get_x() const {
    return this->x;
}
int HexagonButton::get_y() const {
    return this->y;
}
bool HexagonButton::get_color() const {
    if (this->color == Qt::black){
        return false;
    }
    return true;
}
void HexagonButton::set_color(bool color){
    if (color == false) {
        this->color = Qt::black;
    } else {
        this->color = Qt::white;
    }
    update();
}
void HexagonButton::paintEvent(QPaintEvent *event)  {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 创建六边形路径
    QPainterPath hexagonPath;
    int centerX = width() / 2 ;
    int centerY = height() / 2;

    // 计算六边形的顶点
    for (int i = 0; i < 6; ++i) {
        double angle = 2 * M_PI * i / 6;
        int x = centerX + radius * cos(angle);
        int y = centerY + radius * sin(angle);
        if (i == 0) {
            hexagonPath.moveTo(x, y);
        } else {
            hexagonPath.lineTo(x, y);
        }
    }
    hexagonPath.closeSubpath();

    // 绘制六边形
    painter.setPen(Qt::blue);
    painter.setBrush(color);
    painter.drawPath(hexagonPath);

    // 绘制点
    if (this->isPressed) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 设置点的颜色和大小
        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);

        // 计算按钮的中心点

        // 绘制点
        painter.drawEllipse(centerX , centerY , 10, 10);
    }
}

void HexagonButton::mousePressEvent(QMouseEvent *event) {
    // 检查点击是否在六边形内部
    int centerX = width() / 2;
    int centerY = height() / 2;

    // 创建六边形区域
    QPolygon hexagon;
    for (int i = 0; i < 6; ++i) {
        double angle = 2 * M_PI * i / 6;
        int x = centerX + radius * cos(angle);
        int y = centerY + radius * sin(angle);
        hexagon << QPoint(x, y);
    }

    QRegion hexagonRegion(hexagon);

    // 检查点击是否在六边形区域内
    if (hexagonRegion.contains(event->pos())) {
        if (event->button() == Qt::LeftButton) {
            QPushButton::mousePressEvent(event);
        } else if (event->button() == Qt::RightButton) {
            emit rightClicked();
        }
    }
}


void HexagonButton::on_change_color(){
    this->isPressed = true;
    if (this->color == Qt::black){
        this->color =Qt::white;

        update();
    }else{
        this->color =Qt::black;

        update();
    }
}

void HexagonButton::on_change_color_v2(){

    if (this->color == Qt::black){
        this->color =Qt::white;

        update();
    }else{
        this->color =Qt::black;

        update();
    }
}

void HexagonButton::resetbutton(){
    this->color = Qt::white;  // 假设初始颜色为白色
    isPressed = false;  // 重置点击状态为未点击

    update();
}



