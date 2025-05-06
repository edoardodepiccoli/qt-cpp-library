#include <QApplication>
#include <QStringList>
#include "app/controllers/mainwindow.h"
#include "cli/cli.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList args = app.arguments();

    if (args.contains("--cli"))
    {
        CLI cli;
        std::cout << "Running CLI..." << std::endl;
        cli.run();
        return 0;
    }

    MainWindow window;
    window.show();

    return app.exec();
}
