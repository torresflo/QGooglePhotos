#ifndef MAINWINDOWUI_HPP
#define MAINWINDOWUI_HPP

#include <QMainWindow>

class QAction;
class QMenu;
class QFlowLayout;

class MainWindowUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindowUI(QWidget *parent = nullptr);

protected:
    QMenu* m_settingsMenu = nullptr;
    QAction* m_connectionAction = nullptr;

    QMenu* m_navigationMenu = nullptr;
    QAction* m_albumsViewAction = nullptr;

private:
    void createActions();
    void createMenus();
};

#endif // MAINWINDOWUI_HPP
