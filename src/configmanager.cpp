#include "configmanager.h"
#include <QSettings>

// 预览抽图点
#define STARTING_UP_KEY        "StartingUp"
#define STARTING_UP_VALUE      true

ConfigManager *ConfigManager::getInstance()
{
    static ConfigManager cm;
    return &cm;
}

void ConfigManager::setStartingUpEnabled(bool enabled)
{
    m_settings->setValue(STARTING_UP_KEY, enabled);
    m_settings->sync();
}

bool ConfigManager::isStartingUpEnabled()
{
    return m_settings->value(STARTING_UP_KEY, STARTING_UP_VALUE).toBool();
}

ConfigManager::ConfigManager(QObject *parent) : QObject(parent)
{
    m_settings = new QSettings("PunicaStudio");

    addValue(STARTING_UP_KEY, STARTING_UP_VALUE);
}

void ConfigManager::addValue(const QString &key, const QVariant &value)
{
    if( !m_settings->contains(key) )
    {
        m_settings->setValue(key, value);
    }
}
