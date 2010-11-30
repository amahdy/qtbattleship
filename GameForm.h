#ifndef GAMEFORM_H
#define GAMEFORM_H

#include <QWidget>
#include "Square.h"
#include "MainWindow.h"

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


    QHBoxLayout *hlay1[DEFAULT_HEIGHT];

    QHBoxLayout *hlay2[DEFAULT_HEIGHT];

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // GAMEFORM_H
