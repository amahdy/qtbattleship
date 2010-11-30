#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QTime>

namespace Ui {
    class MainWindow;
}

struct action {

    int xy;
    int value;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //A detected ship/water is NEGATIVE
    //A non detected ship is POSITIVE
    //A non detected water is ZERO
    static const int CASE_WATER = 0;
    static const int CASE_WATER_DET = -999;

    static const int CASE_SHIP_1 = 1;
    static const int CASE_SHIP_1_DET = -1;
    static const int CASE_SHIP_2 = 2;
    static const int CASE_SHIP_2_DET = -2;
    static const int CASE_SHIP_3 = 3;
    static const int CASE_SHIP_3_DET = -3;

    static const int BOARD_WIDTH = 5;
    static const int BOARD_HEIGHT = 5;

    int BOARD_1[BOARD_WIDTH*BOARD_HEIGHT]; //First player
    int BOARD_2[BOARD_WIDTH*BOARD_HEIGHT]; //Second player OR Computer player

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //'state' the current available slots in the board (int of locations)
    //@return the decided action location
    int computerClick(QList<int> state);
};

#endif // MAINWINDOW_H
