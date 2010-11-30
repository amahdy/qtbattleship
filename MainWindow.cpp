#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::computerClick(QList<int> state) {

    //Will check in BOARD_1 because computer's board is alwas BOARD_2

    static QList<int> states; //The previous states -if any-
    static QList<int> waitStates; //If detected more than one 'states'

    //No old states,
    if(states.count() == 0) {
        //(1) If no waites -> select a random location:
        if(waitStates.count() == 0) {
            QTime midnight(0, 0, 0);
            qsrand(midnight.secsTo(QTime::currentTime()));
            int selection = qrand() % state.count();

            return state.at(selection);
        }

        //(2) If waites contains element(s):
        states = waitStates;
        waitStates.clear();
    }

    //Get the position of the elements if it's more than one element:
    if(states.count() > 1) {
        int rel = qAbs(state.at(1) - state.at(0));

        //Position -> vertical
        if(rel == BOARD_WIDTH) {

            //Try first direction:
            int elem = state.at(1) - BOARD_WIDTH;
            while(elem > 0) {
                //If BOARD_1[elem] is positive then never detected:
                if(BOARD_1[elem] >= 0) {
                    //Take decision to hit it:
                    return elem;
                }
                elem -= BOARD_WIDTH;
            }

            //Try second direction:
            elem = state.at(1) + BOARD_WIDTH;
            while(elem < BOARD_HEIGHT*BOARD_WIDTH) {
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
            int elem = state.at(1) - 1;
            while(elem > 0) {
                //If BOARD_1[elem] is positive then never detected:
                if(BOARD_1[elem] >= 0) {
                    //Take decision to hit it:
                    return elem;
                }
                elem -= 1;
            }

            //Try second direction:
            elem = state.at(1) + 1;
            while(elem < BOARD_HEIGHT*BOARD_WIDTH) {
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
        return computerClick(state);
    }

    //One only item in states, try to hit any of its neighbours:

    int search = 0;

    //Search in it's right-side:
    search = states.at(0) + 1;
    if(search < BOARD_HEIGHT*BOARD_WIDTH && BOARD_1[search] >= 0) {
        return search;
    }
    //Search in it's top-side:
    search = states.at(0) - BOARD_WIDTH;
    if(search && BOARD_1[search] >= 0) {
        return search;
    }
    //Search in it's bottom-side:
    search = states.at(0) + BOARD_WIDTH;
    if(search < BOARD_HEIGHT*BOARD_WIDTH && BOARD_1[search] >= 0) {
        return search;
    }
    //Search in it's left-side:
    search = states.at(0) - 1;
    if(search && BOARD_1[search] >= 0) {
        return search;
    }
}
