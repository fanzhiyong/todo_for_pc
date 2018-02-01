#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QSystemTrayIcon>
#include "global.h"

namespace Ui {
class Widget;
}

class QTextEdit;
//class QSystemTrayIcon;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    ~Widget();

    void setSizeAndPos();

private:

    void loadQss();

    void loadData();

    void loadTrayIcon();

    void loadConfig();

    QString getText(TextType type);

    QTextEdit * getEdit(TextType type);

private slots:

    void onMenuStartingUp(bool checked);

    void onMenuQuit();

    void onSaveTimeout();

    void onActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::Widget *ui;

    QTimer          * m_saveTimer;

    QSystemTrayIcon * m_trayIcon;
    QMenu           * m_trayIconMenu;
};

#endif // WIDGET_H
