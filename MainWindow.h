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
    static const int BOARD_WEIGHT = BOARD_WIDTH*BOARD_HEIGHT;

    static const int MODE_PLAY_VS_PLAY = 1;
    static const int MODE_PLAY_VS_COMP = 2;

    int BOARD_1[BOARD_WEIGHT]; //First player
    int BOARD_2[BOARD_WEIGHT]; //Second player OR Computer player

    QList<int> state_1; //state for player_1
    QList<int> state_2; //state for player_2

    int game_mode; //MODE_PLAY_VS_PLAY || MODE_PLAY_VS_COMP
    int game_turn; //1 -> player_1 || 2-> player_2


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //@return the decided action location
    int computerClick();

    //@arg1 the player that have its turn (1 or 2)
    //@return void
    void play(int);


};

#endif // MAINWINDOW_H
