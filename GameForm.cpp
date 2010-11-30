#include "GameForm.h"
#include "ui_GameForm.h"

GameForm::GameForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameForm)
{
    ui->setupUi(this);

    vlay = new QVBoxLayout(this);
    for(int i =0 ; i < DEFAULT_HEIGHT ; i++)
    {
        hlay[i] = new QHBoxLayout;
        vlay->addLayout(hlay[i]);
        for( int j =0 ; j < DEFAULT_WIDTH ; j ++)
        {
            hlay[i]->addWidget(&gameSide1[i][j].displayedImageLabel);
        }
    }


}

GameForm::~GameForm()
{
    delete ui;
}
