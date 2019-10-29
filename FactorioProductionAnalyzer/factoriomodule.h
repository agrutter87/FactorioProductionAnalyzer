#ifndef FACTORIO_MODULE_H
#define FACTORIO_MODULE_H

#include <QJsonObject>
#include <QStringList>

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_FACTORIO_MODULE           (0)

/*************************************************************************
 * FactorioModule Class
 *************************************************************************/
class FactorioModule
{
public:
                                        FactorioModule();
                                        FactorioModule(const QJsonObject &json);

private:
    void                                jsonRead(const QJsonObject &json);

    QString                             mCategory;
    QStringList                         mLimitations;
    double                              mModuleEffectConsumption;
    double                              mModuleEffectPollution;
    double                              mModuleEffectProductivity;
    double                              mModuleEffectSpeed;
    QString                             mName;
    double                              mTier;
};

#endif // FACTORIO_MODULE_H
