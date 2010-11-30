#include "GameForm.h"
#include "ui_GameForm.h"

GameForm::GameForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameForm)
{
    ui->setupUi(this);

    for(int i =0 ; i < DEFAULT_HEIGHT ; i++)
    {
        hlay1[i] = new QHBoxLayout;
        ui->player1Lay->addLayout(hlay1[i]);
        for( int j =0 ; j < DEFAULT_WIDTH ; j ++)
        {
            hlay1[i]->addWidget(&gameSide1[i][j].displayedImageBotton);
        }
    }


    for(int i =0 ; i < DEFAULT_HEIGHT ; i++)
    {
        hlay2[i] = new QHBoxLayout;
        ui->player2Lay->addLayout(hlay2[i]);
        for( int j =0 ; j < DEFAULT_WIDTH ; j ++)
        {
            hlay2[i]->addWidget(&gameSide2[i][j].displayedImageBotton);
        }
    }
}

GameForm::~GameForm()
{
    delete ui;
}

void GameForm::on_pushButton_clicked()
{
    ui->gameBoard->setCurrentIndex(0);
}

void GameForm::on_pushButton_2_clicked()
{
    ui->gameBoard->setCurrentIndex(1);
}
