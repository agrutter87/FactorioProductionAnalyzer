#ifndef FACTORIO_MODULE_H
#define FACTORIO_MODULE_H

#include <QJsonObject>

class FactorioModule
{
public:
    FactorioModule();

    void jsonRead(const QJsonObject &json);

private:
    QString mName;
};

#endif // FACTORIO_MODULE_H
