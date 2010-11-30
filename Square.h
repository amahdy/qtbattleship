#ifndef SQUARE_H
#define SQUARE_H

#include <QtGui>
#include <QImage>
#include <QString>
#include <QLabel>

#include "Constants.h"

class Square{
private :
        /**
          * 0 water, 1 ship
          * and i meant to made it int not a bool because it might be changed later
          **/
        int state;
        /**
          * 0 didn't hit yet, 1 is already hit
          **/
        bool hit;

        QImage image;

        int x;
        int y;

        int height;
        int width;

        void reloadImage();
        void changeDisplayedImage(QImage);
        QString getFileName();

        //imageLabel->setPixmap(QPixmap::fromImage(image));
public :
        Square();
       /* Square(int);
        Square(bool);
        Square(int, bool);
*/
        void setImage(QImage);
        void setImage(QString);
        QImage getImage();


        bool getHit();
        void setHit(bool);

        int getState();
        void setState(int);

        int getX();
        void setX(int);

        int getY();
        void setY(int);

        int getHeight();
        void setWidth(int);

        /**
          * this label  will contain the image that displayed for this square
          **/
        QLabel* displayedImageLabel;

        QPushButton displayedImageBotton;
};

#endif // SQUARE_H
