#ifndef CLI_H
#define CLI_H

#include <QObject>
#include <QTextStream>
#include "../models/library.h"

class CLI : public QObject
{
    Q_OBJECT
public:
    explicit CLI(QObject *parent = nullptr);
    void run();

private:
    void processCommand(const QString &command);
    void addItem();
    void removeItem();
    void listItems();
    void showHelp();
    void showError(const QString &message);

    QString readInput(const QString &prompt);
    std::unique_ptr<Item> createItem(const QString &type);

    Library library;
    QTextStream in;
    QTextStream out;
};

#endif // CLI_H