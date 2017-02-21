#include <QtWidgets/QApplication>
#include "TestMainWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CTestMainWidget test;
    test.show();

    return app.exec();
}
