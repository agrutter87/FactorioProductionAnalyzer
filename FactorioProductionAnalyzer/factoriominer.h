#ifndef FACTORIO_MINER_H
#define FACTORIO_MINER_H

#include <QJsonObject>

class FactorioMiner
{
public:
    FactorioMiner();

    void jsonRead(const QJsonObject &json);

private:
    QString mName;
};

#endif // FACTORIO_MINER_H
