#include <QApplication>
#include <QLoggingCategory>

#include <Application/MainWindow.hpp>

int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules("qt.networkauth.*=true");

    QApplication application(argc, argv);
    MainWindow window;
    window.show();

    return application.exec();
}
