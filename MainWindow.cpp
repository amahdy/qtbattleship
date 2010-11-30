#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <iostream>
using namespace std;

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
        state_1.append(i);
    }
    for(int i=0; i<BOARD_WEIGHT; i++) {
        state_2.append(i);
    }

    //Assume PLAYER vs COMPUTER:
    game_mode = MODE_PLAY_VS_COMP;

    //Assume PLAYER_1 turn:
    game_turn = 1;

    //play(game_turn);

    cli_disp();

    play(2, -1);
}

void MainWindow::cli_disp() {

    for (int i=0; i<BOARD_WIDTH; i++) {
        for(int j=0; j<BOARD_HEIGHT; j++) {
            cout << BOARD_1[i*BOARD_WIDTH + j];
        }
        cout<<endl;
    }

    cout<<endl<<endl;

    for (int i=0; i<BOARD_WIDTH; i++) {
        for(int j=0; j<BOARD_HEIGHT; j++) {
            cout << BOARD_2[i*BOARD_WIDTH + j];
        }
        cout<<endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::play(int player, int location) {

    bool playAgain = true;
    int value = 999;
    switch(player) {
    case 1: //player_1
        //Must be a human (not computer)

        value = BOARD_2[location];

        switch(value) {
        case CASE_WATER:
            BOARD_2[location] = CASE_WATER_DET;
            playAgain = false;
            break;
        case CASE_SHIP_1:
            BOARD_2[location] = CASE_SHIP_1_DET;
            break;
        case CASE_SHIP_2:
            BOARD_2[location] = CASE_SHIP_2_DET;
            break;
        case CASE_SHIP_3:
            BOARD_2[location] = CASE_SHIP_3_DET;
            break;
        }
        state_2.removeAt(location);
        break;

    case 2: //player_2
        //Maybe human or maybe computer

        //If computer take the location from the computerClick()
        if(game_mode==MODE_PLAY_VS_COMP) {
            location = computerClick();
            cout << "location by computer: " << location << endl;
        }
        value = BOARD_1[location];

        switch(value) {
        case CASE_WATER:
            BOARD_1[location] = CASE_WATER_DET;
            playAgain = false;
            break;
        case CASE_SHIP_1:
            BOARD_1[location] = CASE_SHIP_1_DET;
            break;
        case CASE_SHIP_2:
            BOARD_1[location] = CASE_SHIP_2_DET;
            break;
        case CASE_SHIP_3:
            BOARD_1[location] = CASE_SHIP_3_DET;
            break;
        }
        state_1.removeAt(location);
        //TODO: need to handle removing states from the computerClick() if it's a ship sinks
        break;
    }

//call update_ui()

    if(playAgain && game_mode==MODE_PLAY_VS_COMP) {
        play(2, -1);
    }
}

void MainWindow::chkComputerStates(int loc, QList<int> current) {
    //If not water then add to my states:
    if(BOARD_1[loc] > 0) {
        current.append(loc);
    }
}

int MainWindow::computerClick() {

    /*
     * VERY IMPORTANT
     * MUST call chkComputerStates(val, states) BEFORE return
     * WHERE 'val' is the designed value to be returned
     */

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

            chkComputerStates(state_1.at(selection), states);
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

                    chkComputerStates(elem, states);
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

                    chkComputerStates(elem, states);
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

                    chkComputerStates(elem, states);
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

                    chkComputerStates(elem, states);
                    return elem;
                }
                elem += 1;
            }
        }

        //Being here means that all directions are already revailed, then it's more than one state:
        waitStates.append(states.at(0));
        states.removeAt(0);

        int ret = computerClick();
        chkComputerStates(ret, states);
        return ret;
    }

    //One only item in states, try to hit any of its neighbours:

    int search = 0;

    //Search in it's right-side:
    search = states.at(0) + 1;
    if(search < BOARD_WEIGHT && BOARD_1[search] >= 0) {
        chkComputerStates(search, states);
        return search;
    }
    //Search in it's top-side:
    search = states.at(0) - BOARD_WIDTH;
    if(search > 0 && BOARD_1[search] >= 0) {
        chkComputerStates(search, states);
        return search;
    }
    //Search in it's bottom-side:
    search = states.at(0) + BOARD_WIDTH;
    if(search < BOARD_WEIGHT && BOARD_1[search] >= 0) {
        chkComputerStates(search, states);
        return search;
    }
    //Search in it's left-side:
    search = states.at(0) - 1;
    if(search > 0 && BOARD_1[search] >= 0) {
        chkComputerStates(search, states);
        return search;
    }
}
