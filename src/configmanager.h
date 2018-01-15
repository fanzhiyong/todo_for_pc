#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>

class QSettings;

class ConfigManager : public QObject
{
    Q_OBJECT
public:

    static ConfigManager * getInstance();

    void setStartingUpEnabled(bool enabled);

    bool isStartingUpEnabled();

private:

    explicit ConfigManager(QObject *parent = 0);

    void addValue(const QString &key, const QVariant &value);

private:

    QSettings * m_settings;
};

#endif // CONFIGMANAGER_H
