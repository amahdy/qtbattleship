#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Declare dummy inits:
    BOARD_1[0] =0;BOARD_1[1] =0;BOARD_1[2] =0;BOARD_1[3] =0;BOARD_1[4] =0;
    BOARD_1[5] =0;BOARD_1[6] =1;BOARD_1[7] =2;BOARD_1[8] =0;BOARD_1[9] =0;
    BOARD_1[10]=0;BOARD_1[11]=0;BOARD_1[12]=2;BOARD_1[13]=0;BOARD_1[14]=0;
    BOARD_1[15]=0;BOARD_1[16]=0;BOARD_1[17]=3;BOARD_1[18]=3;BOARD_1[19]=3;
    BOARD_1[20]=0;BOARD_1[21]=0;BOARD_1[22]=0;BOARD_1[23]=0;BOARD_1[24]=0;

    BOARD_2[0] =1;BOARD_2[1] =0;BOARD_2[2] =0;BOARD_2[3] =0;BOARD_2[4] =0;
    BOARD_2[5] =0;BOARD_2[6] =0;BOARD_2[7] =0;BOARD_2[8] =0;BOARD_2[9] =0;
    BOARD_2[10]=2;BOARD_2[11]=2;BOARD_2[12]=0;BOARD_2[13]=3;BOARD_2[14]=0;
    BOARD_2[15]=0;BOARD_2[16]=0;BOARD_2[17]=0;BOARD_2[18]=3;BOARD_2[19]=0;
    BOARD_2[20]=0;BOARD_2[21]=0;BOARD_2[22]=0;BOARD_2[23]=3;BOARD_2[24]=0;

    //init state_1 & state_2:
    for(int i=0; i<BOARD_WEIGHT; i++) {
        state_1.at(i);
    }
    for(int i=0; i<BOARD_WEIGHT; i++) {
        state_2.at(i);
    }

    //Assume PLAYER vs COMPUTER:
    game_mode = MODE_PLAY_VS_COMP;

    //Assume PLAYER_1 turn:
    game_turn = 1;

    play(game_turn);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::play(int player) {
    switch(player) {
    case 1: //player_1
        //Must be a human (not computer)
        //call update_state()
        //call update_ui()
        break;

    case 2: //player_2
        //If it's a human:
        if(game_mode=MODE_PLAY_VS_PLAY) {
            //call update_state()
            //call update_ui()
        }

        //If it's computer: //game_mode = MODE_PLAY_VS_COMP
        int location = computerClick();
        int value = BOARD_1[location];
        switch(value) {
        case CASE_WATER:
            break;
        case CASE_SHIP_1:
            break;
        case CASE_SHIP_2:
            break;
        case CASE_SHIP_3:
            break;
        }

        break;
    }
}

int MainWindow::computerClick() {

    //Will check in BOARD_1 because computer's board is always BOARD_2
    //Will deal with state_1 because it's always the non-computer state

    static QList<int> states; //The previous states -if any-
    static QList<int> waitStates; //If detected more than one 'states'

    //No old states,
    if(states.count() == 0) {
        //(1) If no waites -> select a random location:
        if(waitStates.count() == 0) {
            QTime midnight(0, 0, 0);
            qsrand(midnight.secsTo(QTime::currentTime()));
            int selection = qrand() % state_1.count();

            return state_1.at(selection);
        }

        //(2) If waites contains element(s):
        states = waitStates;
        waitStates.clear();
    }

    //Get the position of the elements if it's more than one element:
    if(states.count() > 1) {
        int rel = qAbs(state_1.at(1) - state_1.at(0));

        //Position -> vertical
        if(rel == BOARD_WIDTH) {

            //Try first direction:
            int elem = state_1.at(1) - BOARD_WIDTH;
            while(elem > 0) {
                //If BOARD_1[elem] is positive then never detected:
                if(BOARD_1[elem] >= 0) {
                    //Take decision to hit it:
                    return elem;
                }
                elem -= BOARD_WIDTH;
            }

            //Try second direction:
            elem = state_1.at(1) + BOARD_WIDTH;
            while(elem < BOARD_WEIGHT) {
                //If BOARD_1[elem] is positive then never detected:
                if(BOARD_1[elem] >= 0) {
                    //Take decision to hit it:
                    return elem;
                }
                elem += BOARD_WIDTH;
            }
        }

        //Position -> horizontal
        if(rel == 1) {

            //Try first direction:
            int elem = state_1.at(1) - 1;
            while(elem > 0) {
                //If BOARD_1[elem] is positive then never detected:
                if(BOARD_1[elem] >= 0) {
                    //Take decision to hit it:
                    return elem;
                }
                elem -= 1;
            }

            //Try second direction:
            elem = state_1.at(1) + 1;
            while(elem < BOARD_WEIGHT) {
                //If BOARD_1[elem] is positive then never detected:
                if(BOARD_1[elem] >= 0) {
                    //Take decision to hit it:
                    return elem;
                }
                elem += 1;
            }
        }

        //Being here means that all directions are already revailed, then it's more than one state:
        waitStates.append(states.at(0));
        states.removeAt(0);
        return computerClick(state_1);
    }

    //One only item in states, try to hit any of its neighbours:

    int search = 0;

    //Search in it's right-side:
    search = states.at(0) + 1;
    if(search < BOARD_WEIGHT && BOARD_1[search] >= 0) {
        return search;
    }
    //Search in it's top-side:
    search = states.at(0) - BOARD_WIDTH;
    if(search > 0 && BOARD_1[search] >= 0) {
        return search;
    }
    //Search in it's bottom-side:
    search = states.at(0) + BOARD_WIDTH;
    if(search < BOARD_WEIGHT && BOARD_1[search] >= 0) {
        return search;
    }
    //Search in it's left-side:
    search = states.at(0) - 1;
    if(search > 0 && BOARD_1[search] >= 0) {
        return search;
    }
}
