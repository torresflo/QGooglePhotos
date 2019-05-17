#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QScrollArea>

#include <Widgets/QFlowLayout.h>

#include <Application/MainWindowUI.hpp>

MainWindowUI::MainWindowUI(QWidget *parent) : QMainWindow(parent)
{
    createActions();
    createMenus();

    resize(800, 600);
}

void MainWindowUI::createActions()
{
    m_connectionAction = new QAction(this);
    m_connectionAction->setText(tr("Open connection..."));
    m_connectionAction->setShortcut(QKeySequence::Open);
}

void MainWindowUI::createMenus()
{
    m_settingsMenu = menuBar()->addMenu(tr("Settings"));
    m_settingsMenu->addAction(m_connectionAction);
}
