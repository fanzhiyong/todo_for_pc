#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include "compileconfig.h"
#include <QMenu>
#include "configmanager.h"
#include <QDir>
#include <QSettings>

//#include <QSystemTrayIcon>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_saveTimer = new QTimer(this);
    m_saveTimer->setInterval(2000);

    m_trayIcon = new QSystemTrayIcon(this);

    // 托盘图标
    loadTrayIcon();

    // 去掉边框
    setWindowFlags(windowFlags() ^ Qt::FramelessWindowHint);
    // 不显示任务栏图标
    setWindowFlags(windowFlags() ^ Qt::Tool);

    // 加载QSS
    loadQss();

    // 加载数据
    loadData();

    // 加载配置
    loadConfig();

    connect(m_saveTimer, SIGNAL(timeout()), this, SLOT(onSaveTimeout()));
    connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
            SLOT(onActivated(QSystemTrayIcon::ActivationReason)));

    m_saveTimer->start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setSizeAndPos()
{
    QDesktopWidget * desktop = QApplication::desktop();
    QRect desktopRt = desktop->screenGeometry();

    // size
    resize(desktopRt.width()/2.5, desktopRt.height()/2.5);

    // pos
    int x = desktopRt.width() - width() - 2;
    int y = 0;
    setGeometry(x, y, width(), height());
}

void Widget::loadQss()
{
    QFile file(":/res/frame.qss");
    if( file.open(QIODevice::ReadOnly) )
    {
        QString qss = file.readAll();
        file.close();

        setStyleSheet(qss);
    }
}

void Widget::loadData()
{
    QList<TextType> types =
    {
        IMPORTANT_URGENCY, IMPORTANT_NOT_URGENCY, NOT_IMPORTANT_URGENCY, NOT_IMPORTANT_NOT_URGENCY
    };

    foreach (auto type, types)
    {
        QString text = readText(type);
        m_saveData[type] = text;
        QTextEdit * edit = getEdit(type);
        if( edit != NULL )
        {
            edit->setPlainText(text);
        }
    }
}

void Widget::loadTrayIcon()
{
    m_trayIconMenu = new QMenu(this);
    // 菜单
    // 开机启动
    QAction * action = m_trayIconMenu->addAction("Starting up", this, SLOT(onMenuStartingUp(bool)));
    action->setCheckable(true);
    ConfigManager * cm = ConfigManager::getInstance();
    action->setChecked(cm->isStartingUpEnabled());

    // 退出
    m_trayIconMenu->addAction("Quit", this, SLOT(onMenuQuit()));
    m_trayIcon->setContextMenu(m_trayIconMenu);

    // 托盘图标
    m_trayIcon->setIcon(QIcon(":/res/image/tray_icon.png"));
    m_trayIcon->setToolTip("Todo for pc");
    m_trayIcon->show();
}

void Widget::loadConfig()
{
    ConfigManager * cm = ConfigManager::getInstance();
    onMenuStartingUp(cm->isStartingUpEnabled());
}

QString Widget::getText(TextType type)
{
    QTextEdit * edit = getEdit(type);
    if( edit != NULL )
    {
        return edit->toPlainText();
    }
    else
    {
        return "";
    }
}

void Widget::saveText(TextType type, const QString &text)
{
    QFile file(getFileName(type));
    if( file.open(QIODevice::WriteOnly) )
    {
        m_saveData[type] = text;
        file.write(text.toUtf8());
        file.close();
    }
}

QString Widget::readText(TextType type)
{
    QFile file(getFileName(type));
    if( file.open(QIODevice::ReadOnly) )
    {
        return file.readAll();
    }

    return "";
}

QTextEdit *Widget::getEdit(TextType type)
{
    switch( type )
    {
    case IMPORTANT_URGENCY:
        return ui->importAndUrgencyEdit;
    case IMPORTANT_NOT_URGENCY:
        return ui->importAndNotUrgencyEdit;
    case NOT_IMPORTANT_URGENCY:
        return ui->notImportAndUrgencyEdit;
    case NOT_IMPORTANT_NOT_URGENCY:
        return ui->notImportAndNotUrgencyEdit;
    default:
        return NULL;
    }
}

QString Widget::getFileName(TextType type)
{
    switch( type )
    {
    case IMPORTANT_URGENCY:
        return "important_urgency.txt";
    case IMPORTANT_NOT_URGENCY:
        return "important_not_urgency.txt";
    case NOT_IMPORTANT_URGENCY:
        return "not_important_urgency.txt";
    case NOT_IMPORTANT_NOT_URGENCY:
        return "not_important_not_urgency.txt";
    default:
        return "";
    }
}

void Widget::onMenuStartingUp(bool checked)
{
    ConfigManager * cm = ConfigManager::getInstance();
    cm->setStartingUpEnabled(checked);

    // 设置开机启动
    QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if (checked)
    {
        QString strAppPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
        reg.setValue("TodoForPc", strAppPath);
    }
    else
    {
        reg.setValue("TodoForPc", "");
    }

}

void Widget::onMenuQuit()
{
    m_trayIcon->hide();
    QApplication::quit();
}

void Widget::onSaveTimeout()
{
    // 当前目录下
    QList<TextType> types =
    {
        IMPORTANT_URGENCY, IMPORTANT_NOT_URGENCY, NOT_IMPORTANT_URGENCY, NOT_IMPORTANT_NOT_URGENCY
    };

    foreach (auto type, types)
    {
        if( getText(type) != m_saveData[type] )
        {
            saveText(type, getText(type));
        }
    }
}

void Widget::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    if( reason == QSystemTrayIcon::Trigger )
    {
        activateWindow();
    }
}
