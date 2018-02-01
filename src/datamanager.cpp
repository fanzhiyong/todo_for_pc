#include "datamanager.h"
#include "json.hpp"
#include <QFile>
#include <QDir>

using json = nlohmann::json;

DataManager::DataManager(QObject *parent) : QObject(parent)
{
    // read data
    read();
}

void DataManager::read()
{
    QFile file(getFilePath());
    if( file.open(QIODevice::ReadOnly) )
    {
        QString text = file.readAll();
        file.close();

        try
        {
            json root = json::parse(text.toStdString());
            m_data[IMPORTANT_URGENCY]         = root["iu"].get<std::string>().c_str();
            m_data[IMPORTANT_NOT_URGENCY]     = root["inu"].get<std::string>().c_str();
            m_data[NOT_IMPORTANT_URGENCY]     = root["niu"].get<std::string>().c_str();
            m_data[NOT_IMPORTANT_NOT_URGENCY] = root["ninu"].get<std::string>().c_str();
        }catch(std::exception e)
        {
            Q_UNUSED(e);
        }
    }
}

void DataManager::save()
{
    QFile file(getFilePath());
    if( file.open(QIODevice::WriteOnly) )
    {
        json root;

        root["iu"]   = m_data[IMPORTANT_URGENCY].toStdString();
        root["inu"]  = m_data[IMPORTANT_NOT_URGENCY].toStdString();
        root["niu"]  = m_data[NOT_IMPORTANT_URGENCY].toStdString();
        root["ninu"] = m_data[NOT_IMPORTANT_NOT_URGENCY].toStdString();

        file.write(root.dump(4).c_str());
        file.close();
    }
}

QString DataManager::getFilePath()
{
    QString path = QDir::homePath() + "/AppData/Roaming/TodoForPc";
    QDir().mkpath(path);

    return path + "/data.json";
}

DataManager *DataManager::getInstance()
{
    static DataManager dm;
    return &dm;
}

QString DataManager::getData(TextType type)
{
    return m_data[type];
}

void DataManager::setData(TextType type, const QString &text)
{
    if( m_data[type] != text )
    {
        m_data[type] = text;
        save();
    }
}
