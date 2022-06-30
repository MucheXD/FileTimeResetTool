#include "Resetter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Resetter resetterWindow;
    resetterWindow.show();
    resetterWindow.getAllFileList(argc, argv);
    int retCode = app.exec();
    if (retCode != 0)
    {
        fullWindowInfo* fwi = new fullWindowInfo;
        fwi->setInfo("crash", QString("The program exit unexpectedly. Code=%1.").arg(retCode));
        fwi->show();
        app.exec();
    }
}
