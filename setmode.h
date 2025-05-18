#ifndef SETMODE_H
#define SETMODE_H

#include <QWidget>
#include <QList>
#include "level.h"
#include "hexbotto.h"
#include <QFileDialog>
#include <QVBoxLayout>

class Setmode : public Level
{
    Q_OBJECT
public:
    Setmode();
    void onSaveButtonClicked();
    void change_layer(HexagonButton* cur_button);
};

#endif // SETMODE_H
