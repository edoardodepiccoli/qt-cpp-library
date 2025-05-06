#include "cli.h"
#include <QCoreApplication>
#include <QDebug>
#include "../visitors/debugvisitor.h"

CLI::CLI(QObject *parent)
    : QObject(parent), in(stdin), out(stdout)
{
}

void CLI::run()
{
    out << "Qt Library Management System\n";
    out << "Type 'help' for available commands\n\n";

    while (true)
    {
        QString command = readInput("> ").trimmed().toLower();
        if (command == "exit" || command == "quit")
        {
            break;
        }
        processCommand(command);
    }
}

void CLI::processCommand(const QString &command)
{
    if (command == "help")
    {
        showHelp();
    }
    else if (command == "add")
    {
        addItem();
    }
    else if (command == "remove")
    {
        removeItem();
    }
    else if (command == "list")
    {
        listItems();
    }
    else
    {
        showError("Unknown command. Type 'help' for available commands.");
    }
}

void CLI::addItem()
{
    out << "Enter item type (book/movie/article): ";
    QString type = readInput("Type: ").trimmed().toLower();

    if (type != "book" && type != "movie" && type != "article")
    {
        showError("Invalid item type. Please choose: book, movie, or article");
        return;
    }

    auto item = createItem(type);
    if (item)
    {
        library.addItem(std::move(item));
        out << "Item added successfully!\n";
    }
}

void CLI::removeItem()
{
    listItems();
    if (library.getItemCount() == 0)
    {
        return;
    }

    out << "Enter item number to remove: ";
    bool ok;
    int index = readInput("Index: ").toInt(&ok);

    if (!ok || index < 1 || index > library.getItemCount())
    {
        showError("Invalid item number");
        return;
    }

    library.removeItem(index - 1);
    out << "Item removed successfully!\n";
}

void CLI::listItems()
{
    if (library.getItemCount() == 0)
    {
        out << "No items in library.\n";
        return;
    }

    DebugVisitor debugVisitor;
    library.accept(debugVisitor);
}

void CLI::showHelp()
{
    out << "\nAvailable commands:\n";
    out << "  add    - Add a new item (book/movie/article)\n";
    out << "  remove - Remove an item by number\n";
    out << "  list   - List all items\n";
    out << "  help   - Show this help message\n";
    out << "  exit   - Exit the program\n\n";
}

void CLI::showError(const QString &message)
{
    out << "Error: " << message << "\n";
}

QString CLI::readInput(const QString &prompt)
{
    out << prompt;
    out.flush();
    return in.readLine();
}

std::unique_ptr<Item> CLI::createItem(const QString &type)
{
    QString title = readInput("Enter title: ");
    QString description = readInput("Enter description: ");

    bool ok;
    out << "Enter year: ";
    int year = readInput("Year: ").toInt(&ok);
    if (!ok)
    {
        showError("Invalid year");
        return nullptr;
    }

    out << "Enter review (1-5): ";
    int review = readInput("Review: ").toInt(&ok);
    if (!ok || review < 1 || review > 5)
    {
        showError("Invalid review. Please enter a number between 1 and 5");
        return nullptr;
    }

    QString comment = readInput("Enter comment: ");

    std::unique_ptr<Item> item;
    if (type == "book")
    {
        QString author = readInput("Enter author: ");
        item = std::make_unique<Book>(title, description, year, review, comment, author);
    }
    else if (type == "movie")
    {
        QString director = readInput("Enter director: ");
        item = std::make_unique<Movie>(title, description, year, review, comment, director);
    }
    else if (type == "article")
    {
        QString link = readInput("Enter link: ");
        item = std::make_unique<Article>(title, description, year, review, comment, link);
    }

    return item;
}