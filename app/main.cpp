#include <QCoreApplication>
#include "cli/cli.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CLI cli;
    std::cout << "Running CLI...";
    cli.run();

    return 0;
}