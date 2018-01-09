#include "widget.h"
#include <QApplication>
#include "QtSingleApplication"
#include "compileconfig.h"

int main(int argc, char *argv[])
{
    QtSingleApplication a(argc, argv);

    if( a.isRunning() )
    {
        a.sendMessage("topShow", 1000);
        return 0;
    }

    Widget w;
    w.show();
    w.setSizeAndPos();

    return a.exec();
}
