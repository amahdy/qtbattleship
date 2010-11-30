#include "Square.h"

Square::Square()
{
    this->reloadImage();
}

Square::Square(int state)
{
    this->setState(state);

}
Square::Square(bool hit)
{
    this->setHit(hit);
}
Square::Square(int state, bool hit)
{
    this->state = state;
    this->hit = hit;

    this->reloadImage();
}
Square::Square(int state, bool hit, int height, int width)
{

}
Square::Square(int state, bool hit, int height, int width, int x, int y)
{
    this->Square();
}

void Square::setImage(QImage image)
{
   this->image =  image;
}

void Square::setImage(QString fileName)
{
   this->image.load(fileName);
}

QImage Square::getImage()
{
    return this->image;
}

void Square::reloadImage()
{
    this->setImage(this->getFileName());
    this->changeDisplayedImage(this->getImage());
}

void Square::changeDisplayedImage(QImage image)
{
    this->displayedImageLabel->setPixmap(QPixmap::fromImage(image));
}

bool Square::getHit()
{
    return this->hit;
}
void Square::setHit(bool hit)
{
    this->hit = hit;
    this->reloadImage();
}
int Square::getState()
{
    return this->state;
}
void Square::setState(int state)
{
    this->state = state;
    this->reloadImage();
}

QString Square::getFileName()
{
    if(this->state == 0 && this->hit == 0)
    {
        return WATER_FILE_NAME;
    }
    else if(this->state == 0 && this->hit == 1)
    {
        return HIT_WATER_FILE_NAME;
    }
    else if(this->state == 1 && this->hit == 0){
        return SHIP_PART_FILE_NAME;
    }
    else if(this->state == 1 && this->hit == 1)
    {
        return HIT_SHIP_PART_FILE_NAME;
    }
}

int Square::getX()
{
    return this->x;
}
void Square::setX(int x)
{
    this->x = x;
}
int Square::getY()
{
    return y;
}
void Square::setY(int y)
{
    this->y = y;
}
int Square::getHeight()
{
    return this->height;
}
void Square::setWidth(int width)
{
    this->width = width;
}
Square::~Square()
{

}

