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
    BOARD_1[5] =0;BOARD_1[6] =0;BOARD_1[7] =2;BOARD_1[8] =0;BOARD_1[9] =0;
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

    //test:
    played = 0;

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

    /*
    for (int i=0; i<BOARD_WIDTH; i++) {
        for(int j=0; j<BOARD_HEIGHT; j++) {
            cout << BOARD_2[i*BOARD_WIDTH + j];
        }
        cout<<endl;
    }*/

    //cout<<endl<<endl<<endl;

    /*
    for(int i=0; i<BOARD_WIDTH; i++) {
        for(int j=0; j<BOARD_HEIGHT; j++) {

        }
    }*/

    for(int i=0; i<state_1.count(); i++) {
        cout << state_1.at(i) << " -- ";
    }
    cout<<endl;
    for(int i=0; i<cpu_states.count(); i++) {
        cout << cpu_states.at(i) << " -- ";
    }
    cout<<endl<<endl;
    /*
    for(int i=0; i<state_2.count(); i++) {
        cout << state_2.at(i) << endl;
    }*/
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

        //if it's a complete ship
        if(cpu_states.count() > 1) {
            int count = 1;
            for(int i=1, prev=BOARD_1[cpu_states.at(0)]; i<cpu_states.count(); i++) {
                if(BOARD_1[cpu_states.at(i)] != prev) {
                    break;
                }
                count++;
            }
            if(-1*count == BOARD_1[cpu_states.at(0)]) {
                cpu_states.clear();
            }
        }

        break;
    }

//call update_ui()

    cli_disp();

    if(playAgain && game_mode==MODE_PLAY_VS_COMP  && played < 20) {
        played ++;
        play(2, -1);
    }

    //test to play again:
    cout<<"***** PLAY AGAIN:" << endl << endl;
    if(state_1.count() > 0 && played < 20) {
        played ++;
        play(2, -1);
    }
}

void MainWindow::chkComputerStates(int loc) {
    //If not water then add to my states:
    if(BOARD_1[loc] > 0) {
        cpu_states.append(loc);
    }
}

int MainWindow::computerClick() {

    /*
     * VERY IMPORTANT
     * MUST call chkComputerStates(val) BEFORE return
     * WHERE 'val' is the designed value to be returned
     */

    //Will check in BOARD_1 because computer's board is always BOARD_2
    //Will deal with state_1 because it's always the non-computer state



    //No old states,
    if(cpu_states.count() == 0) {
        //(1) If no waites -> select a random location:
        if(cpu_waitStates.count() == 0) {
            QTime midnight(0, 0, 0);
            qsrand(midnight.secsTo(QTime::currentTime()));
            int selection = qrand() % state_1.count();

            chkComputerStates(state_1.at(selection));
            return state_1.at(selection);
            //chkComputerStates(12);
            //return 12;
        }

        //(2) If waites contains element(s):
        cpu_states = cpu_waitStates;
        cpu_waitStates.clear();
    }

    //Get the position of the elements if it's more than one element:
    if(cpu_states.count() > 1) {
        int rel = qAbs(cpu_states.at(1) - cpu_states.at(0));

        //Position -> vertical
        if(rel == BOARD_WIDTH) {

            //Try first direction:
            int elem = cpu_states.at(1) - BOARD_WIDTH; //result should not be negative
            while(elem > 0 && BOARD_1[elem] != CASE_WATER_DET) {
                //If BOARD_1[elem] is positive then never detected:
                if(BOARD_1[elem] >= 0) {
                    //Take decision to hit it:

                    chkComputerStates(elem);
                    return elem;
                }
                elem -= BOARD_WIDTH;
            }

            //Try second direction:
            elem = cpu_states.at(1) + BOARD_WIDTH; //result should not be out of weight
            while(elem < BOARD_WEIGHT && BOARD_1[elem] != CASE_WATER_DET) {
                //If BOARD_1[elem] is positive then never detected:
                if(BOARD_1[elem] >= 0) {
                    //Take decision to hit it:

                    chkComputerStates(elem);
                    return elem;
                }
                elem += BOARD_WIDTH;
            }
        }

        //Position -> horizontal
        if(rel == 1) {

            //Try first direction:
            int elem = cpu_states.at(1) - 1; //% result is in [0, 1, 2, 3]
            while(elem % BOARD_WIDTH < 4 && BOARD_1[elem] != CASE_WATER_DET) {
                //If BOARD_1[elem] is positive then never detected:
                if(BOARD_1[elem] >= 0) {
                    //Take decision to hit it:

                    chkComputerStates(elem);
                    return elem;
                }
                elem -= 1;
            }

            //Try second direction:
            elem = cpu_states.at(1) + 1; //% result is in [1, 2, 3, 4]
            while(elem % BOARD_WIDTH != 0 && BOARD_1[elem] != CASE_WATER_DET) {
                //If BOARD_1[elem] is positive then never detected:
                if(BOARD_1[elem] >= 0) {
                    //Take decision to hit it:

                    chkComputerStates(elem);
                    return elem;
                }
                elem += 1;
            }
        }

        //Being here means that all directions are already revailed, then it's more than one state:
        cpu_waitStates.append(cpu_states.at(0));
        cpu_states.removeAt(0);

        int ret = computerClick();
        chkComputerStates(ret);
        return ret;
    }

    //One only item in states, try to hit any of its neighbours:

    int search = 0;

    //Search in it's right-side:
    search = cpu_states.at(0) + 1; //% result should be in [1, 2, 3, 4]
    if(search % BOARD_WIDTH != 0 && BOARD_1[search] >= 0 && BOARD_1[search] != CASE_WATER_DET) {
        chkComputerStates(search);
        return search;
    }
    //Search in it's top-side:
    search = cpu_states.at(0) - BOARD_WIDTH;
    if(search > 0 && BOARD_1[search] >= 0 && BOARD_1[search] != CASE_WATER_DET) {
        chkComputerStates(search);
        return search;
    }
    //Search in it's bottom-side:
    search = cpu_states.at(0) + BOARD_WIDTH;
    if(search < BOARD_WEIGHT && BOARD_1[search] >= 0 && BOARD_1[search] != CASE_WATER_DET) {
        chkComputerStates(search);
        return search;
    }
    //Search in it's left-side:
    search = cpu_states.at(0) - 1; //% result should be in [0, 1, 2, 3]
    if(search % BOARD_WIDTH < 4 && BOARD_1[search] >= 0 && BOARD_1[search] != CASE_WATER_DET) {
        chkComputerStates(search);
        return search;
    }
}
