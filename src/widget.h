#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QSystemTrayIcon>

namespace Ui {
class Widget;
}

class QTextEdit;
//class QSystemTrayIcon;

enum TextType
{
    IMPORTANT_URGENCY,
    IMPORTANT_NOT_URGENCY,
    NOT_IMPORTANT_URGENCY,
    NOT_IMPORTANT_NOT_URGENCY
};

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

    QString getText(TextType type);

    void saveText(TextType type, const QString & text);

    QString readText(TextType type);

    QTextEdit * getEdit(TextType type);

    QString getFileName(TextType type);

private slots:

    void onSaveTimeout();

    void onActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::Widget *ui;

    QMap<TextType, QString> m_saveData;
    QTimer * m_saveTimer;

    QSystemTrayIcon * m_trayIcon;
    QMenu           * m_trayIconMenu;
};

#endif // WIDGET_H
