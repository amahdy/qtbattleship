#include <QtGui/QApplication>
#include "MainWindow.h"
// for testing
#include "GameForm.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //for testing
    GameForm w;
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    return a.exec();
}
