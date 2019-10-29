#ifndef FACTORIO_ASSEMBLER_H
#define FACTORIO_ASSEMBLER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_FACTORIO_ASSEMBLER        (0)

/*************************************************************************
 * FactorioAssembler Class
 *************************************************************************/
class FactorioAssembler
{
public:
                                        FactorioAssembler();
                                        FactorioAssembler(const QJsonObject &json);

private:
    void                                jsonRead(const QJsonObject &json);

    bool                                mAllowedEffectConsumption;
    bool                                mAllowedEffectPollution;
    bool                                mAllowedEffectProductivity;
    bool                                mAllowedEffectSpeed;
    QStringList                         mCraftingCategories;
    double                              mCraftingSpeed;
    double                              mIngredientCount;
    double                              mModuleInventorySize;
    QString                             mName;
};

#endif // FACTORIO_ASSEMBLER_H
