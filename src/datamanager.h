#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include "global.h"
#include <QMap>

class DataManager : public QObject
{
    Q_OBJECT
public:

    static DataManager * getInstance();

    QString getData(TextType type);

    void setData(TextType type, const QString & text);

private:

    explicit DataManager(QObject *parent = 0);

    void read();

    void save();

    QString getFilePath();

private:

    QMap<int, QString> m_data;
};

#endif // DATAMANAGER_H
