#ifndef FACTORIO_MINER_H
#define FACTORIO_MINER_H

#include <QJsonObject>
#include <QStringList>

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_FACTORIO_MINER            (0)

/*************************************************************************
 * FactorioMiner Class
 *************************************************************************/
class FactorioMiner
{
public:
                                        FactorioMiner();
                                        FactorioMiner(const QJsonObject &json);

    QString                             getName() const;

private:
    void                                jsonRead(const QJsonObject &json);

    bool                                mAllowedEffectConsumption;
    bool                                mAllowedEffectPollution;
    bool                                mAllowedEffectProductivity;
    bool                                mAllowedEffectSpeed;
    double                              mMiningSpeed;
    QString                             mName;
    QStringList                         mResourceCategories;
};

#endif // FACTORIO_MINER_H
