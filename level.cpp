#include "level.h"
#define X 45
#define Y 26
#define Yy 52

Level::Level(QString name,int layer ) :last_button(NULL),question_name(name),total_stride_length(0)
{
    int layers = 0;
    this->widget = new QWidget;
    widget->setFixedSize(1600,900);
    this->button_map=QList<QList<HexagonButton*>>();
    this->button_map.resize(this->loadButtonStatesLayers(name)+1);

    //给setmode留的
    if (layer == 0) {
        bool ok;
        layers = QInputDialog::getInt(this->widget, "Input Dialog", "Enter number of layers:", 4, 1, 10, 1, &ok);

        if (ok) {
            this->button_map.resize(layers+1);
            generateHexagonMap(layers); // 使用用户输入的层数生成地图
        } else {
            MainWindow *newWindow = new MainWindow();
            newWindow->show();
            this->widget->close();
            disconnect(this, nullptr, nullptr, nullptr);
            this->deleteLater();
        }
    }
    generateHexagonMap(this->loadButtonStatesLayers(name));
    this->loadButtonStates(name);


    // generateHexagonMap(4);
    // if(!name.isEmpty()){
    //     this->loadButtonStates(name);
    // }

    widget->show();

    QPushButton* backButton = new QPushButton("back", this->widget);
    connect(backButton, &QPushButton::clicked, this, [this](){
        MainWindow *newWindow = new MainWindow();
        newWindow->show();
        this->widget->close();
        disconnect(this, nullptr, nullptr, nullptr);
        this->deleteLater();
    });
    backButton->move(0,50);
    backButton->show();
}

HexagonButton* Level::setButtonPosition(QWidget* widget,int x, int y){
    HexagonButton *centerButton = new HexagonButton(widget, x , y );
    HexagonButton::connect(centerButton, &HexagonButton::pressed, this, [centerButton,this](){
        this->handle_click(centerButton);
    });
    return centerButton;
}

void Level::generateHexagonMap(int layers) {
    // 计算每层的六边形数量和位置
    int centerX = 0;
    int centerY = 0;

    // 中心六边形
    HexagonButton *centerButton = new HexagonButton(this->widget, centerX , centerY );
    connect(centerButton, &HexagonButton::pressed, this, [centerButton,this](){
        this->handle_click(centerButton);
    });
    this->button_map[0].append(centerButton);

    // 生成每层六边形
    for(int i =1;i<=layers;i++){
        int count =i+1;
        //左边
        for (int j = 0; j<count;j++){
            //偏移量
            int x = -X*i;
            int y = -Y*i+Yy*j;
            this->button_map[i].append(setButtonPosition(this->widget,x,y));
        }
        //右边
        for (int j = 0; j<count;j++){
            //偏移量
            int x = X*i;
            int y = -Y*i+Yy*j;
          this->button_map[i].append(setButtonPosition(this->widget,x,y));
        }

        //上面
        HexagonButton *topButton = new HexagonButton(this->widget, 0 , -Yy*i );
        connect(topButton, &HexagonButton::pressed, this, [topButton,this](){
            this->handle_click(topButton);
        });
        this->button_map[i].append(topButton);

        //下面
        HexagonButton *bottomButton = new HexagonButton(this->widget, 0 , Yy*i );
        connect(bottomButton, &HexagonButton::pressed,this, [bottomButton,this](){
            this->handle_click(bottomButton);
        });
        this->button_map[i].append(bottomButton);

        //左上
        for(int j = 0; j<i-1;j++){
            int x = -X*(i-1-j);
            int y = -Y*(i+1+j);
            this->button_map[i].append(setButtonPosition(this->widget,x,y));
        }
        //右上
        for(int j = 0; j<i-1;j++){
            int x = X*(i-1-j);
            int y = -Y*(i+1+j);
            this->button_map[i].append(setButtonPosition(this->widget,x,y));
        }
        //左下
        for(int j = 0; j<i-1;j++){
            int x = -X*(i-1-j);
            int y = Y*(i+1+j);
             this->button_map[i].append(setButtonPosition(this->widget,x,y));
        }
        //右下
        for(int j = 0; j<i-1;j++){
            int x = X*(i-1-j);
            int y = Y*(i+1+j);
             this->button_map[i].append(setButtonPosition(this->widget,x,y));
        }
    }
}


bool Level::is_neibor(HexagonButton* next_button){
    if (last_button == NULL) {
        return true;
    }
    bool is_neibor = false;
    int offset_x = next_button->get_x() - this->last_button->get_x();
    int offset_y = next_button->get_y() - last_button->get_y();
    if ((offset_x == X) || (offset_x == -X)){
        if ((offset_y == Y) || (offset_y == -Y) ){
            is_neibor = true;
        }
    }
    if (offset_x == 0){
        if ((offset_y == Yy) || (offset_y == -Yy)){
            is_neibor = true;
        }
    }
    return is_neibor;
}

bool Level::is_no_store(HexagonButton* cur_button ){
    for (const HexagonButton* store_button : this->store_button_map) {
        if (cur_button->get_x() == store_button->get_x() && cur_button->get_y() == store_button->get_y()){
            return false;
        }
    }
    return true;
}

void Level::store(HexagonButton* cur_button){
    this->store_button_map.append(cur_button);
    this->last_button = cur_button;
}

void Level::change_color(HexagonButton* cur_button){
    cur_button->on_change_color();
}

bool Level::is_finish(){
    for(QList<HexagonButton*> layer : this->button_map){
        HexagonButton* base_button = layer[0];
        for(HexagonButton* button : layer){
            if (button->get_color() != base_button->get_color()){
                return false;
            }
        }
    }
    return true;
}

void Level::handle_click(HexagonButton* cur_button){
    this->stride_length += 1;
    this->total_stride_length += 1;
    if (this->is_neibor(cur_button) && this->is_no_store(cur_button)){
        this->store(cur_button);
        this->change_color(cur_button);
        if (this->is_finish()) {
            //游戏胜利结算
             resultWindow();
            this->try_time = 0;
            // this->reset_page();
            // this->loadButtonStates(question_name);
        }
        //继续做题，什么都不发神
    } else {
        //重置题面
        this->reset_page();
        this->loadButtonStates(question_name);
    }
}

void Level::reset_page(){
    for(QList<HexagonButton*> layer : this->button_map){
        for(HexagonButton* button : layer){
            button->resetbutton();
        }
    }
    this -> last_button = NULL;
    this->store_button_map.clear();
    this->stride_length = 0;
}

void Level::saveButtonStates(const QString& filename) {
    QJsonArray mapArray;

    for (const QList<HexagonButton*>& layer : button_map) {
        QJsonArray layerArray;
        for (HexagonButton* button : layer) {
            if (!button) continue;

            QJsonObject buttonObj;
            buttonObj["x"] = button->get_x();
            buttonObj["y"] = button->get_y();
            buttonObj["color"] = button->get_color();

            layerArray.append(buttonObj);
        }
        mapArray.append(layerArray);
    }

    QJsonDocument doc(mapArray);

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

int Level::loadButtonStates(const QString& filename) {
    QFile file(filename);
    if (!file.exists()) {
        qWarning() << "文件不存在：" << filename;
        return false;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "无法打开文件进行读取：" << file.errorString();
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        qWarning() << "JSON解析失败！";
        return false;
    }

    if (!doc.isArray()) {
        qWarning() << "JSON文档不是数组！";
        return false;
    }

    QJsonArray mapArray = doc.array();
    //int layers = qMin(mapArray.size(), button_map.size());
    int layers = mapArray.size();
    for (int i = 0; i < layers; ++i) {
        QJsonArray layerArray = mapArray[i].toArray();
        QList<HexagonButton*>& layer = button_map[i];
        int buttons = qMin(layerArray.size(), layer.size());

        for (int j = 0; j < buttons; ++j) {
            QJsonObject buttonObj = layerArray[j].toObject();
            HexagonButton* button = layer[j];

            if (buttonObj.contains("color") && buttonObj["color"].isBool()) {
                button->set_color(buttonObj["color"].toBool());
            } else {
                qWarning() << "JSON对象中没有颜色信息或格式错误：" << buttonObj;
            }
        }
    }

    this->try_time +=1;
    // 强制更新窗口以显示更改
    this->update();

    qDebug() << "文件加载成功：" << filename;
    return layers;
}

int Level::loadButtonStatesLayers(const QString& filename) {
    QFile file(filename);
    if (!file.exists()) {
        qWarning() << "文件不存在：" << filename;
        return false;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "无法打开文件进行读取：" << file.errorString();
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        qWarning() << "JSON解析失败！";
        return false;
    }

    if (!doc.isArray()) {
        qWarning() << "JSON文档不是数组！";
        return false;
    }
    QJsonArray mapArray = doc.array();
    int layers = mapArray.size();
    return layers-1;
}

void Level::resultWindow() {

    QWidget * resultwindow = new QWidget();
    setWindowTitle("Game Result");
    resultwindow->setFixedSize(640,360);

    // 创建布局
    QVBoxLayout *layout = new QVBoxLayout(resultwindow);

    // 添加一个标签显示游戏结果
    QLabel *resultLabel = new QLabel("Congratulations! You Win!\n这一次你使用了"
    +QString::number(this->stride_length)+"步\n你尝试了"+QString::number(this->try_time + 1)+"次\n"+
    "你总计走了"+QString::number( total_stride_length)+ "步", resultwindow);
    QFont font = resultLabel->font();
    font.setPointSize(24); // 设置字号为24
    resultLabel->setFont(font);
    resultLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(resultLabel);

    // 添加一个按钮用于重新开始游戏
    QPushButton *restartButton = new QPushButton("回到主菜单", resultwindow);
    layout->addWidget(restartButton);

    // 连接按钮的点击信号到槽函数
    connect(restartButton, &QPushButton::clicked, resultwindow, [this,resultwindow](){
        MainWindow *newWindow = new MainWindow();
        newWindow->show();
        this->widget->close();
        disconnect(this, nullptr, nullptr, nullptr);
        this->deleteLater();
        resultwindow->close();
        delete resultwindow;
    });

    resultwindow->show();
}






