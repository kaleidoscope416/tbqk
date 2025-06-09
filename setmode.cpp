#include "setmode.h";

Setmode::Setmode() : Level("",0,1){

    for(QList<HexagonButton*> layer : this->button_map){
        for(HexagonButton* button : layer){
            HexagonButton::connect(button, &HexagonButton::rightClicked, this, [button,this](){
                this->change_layer(button);
            });
        }
    }
    QPushButton* saveButton = new QPushButton("Save", this->widget);
    connect(saveButton, &QPushButton::clicked, this, &Setmode::onSaveButtonClicked);
    saveButton->show();

}

void Setmode::change_layer(HexagonButton* cur_button){
    for(QList<HexagonButton*> layer : this->button_map){
        bool is_layer = false;
        for(HexagonButton* button : layer){
            if (button->get_x() == cur_button->get_x() && button->get_y() == cur_button->get_y()){
                is_layer = true;
            }
        }
        if (is_layer){
            for(HexagonButton* button : layer){
                button->on_change_color_v2();
            }
        }
    }
}

void Setmode::onSaveButtonClicked() {
    QString filename = QFileDialog::getSaveFileName(this, "Save Button States", "", "JSON Files (*.json)");
    if (!filename.isEmpty()) {
        saveButtonStates(filename);
    }
}

void Setmode::getUserId(QWidget* parent) {
    bool ok;
    QString userId = QInputDialog::getText(parent,
                                           "输入用户ID",
                                           "请输入您的用户ID：",
                                           QLineEdit::Normal,
                                           "",
                                           &ok);
    if (ok && !userId.isEmpty()) {
        playName = userId;
    } else {
        // 用户取消或未输入，可给默认值或退出
        playName = "匿名";
    }
}


