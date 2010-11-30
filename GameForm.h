#ifndef GAMEFORM_H
#define GAMEFORM_H

#include <QWidget>
#include "Square.h"

namespace Ui {
    class GameForm;
}

class GameForm : public QWidget
{
    Q_OBJECT

public:
    explicit GameForm(QWidget *parent = 0);
    ~GameForm();

private:
    Ui::GameForm *ui;


    Square gameSide1[DEFAULT_HEIGHT][DEFAULT_WIDTH];
    Square gameSide2[DEFAULT_HEIGHT][DEFAULT_WIDTH];

    QVBoxLayout *vlay;
    QHBoxLayout *hlay[DEFAULT_HEIGHT];
};

#endif // GAMEFORM_H
