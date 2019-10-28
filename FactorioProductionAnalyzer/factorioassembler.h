#ifndef FACTORIO_ASSEMBLER_H
#define FACTORIO_ASSEMBLER_H

#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>

class FactorioAssembler
{
public:
    FactorioAssembler();

    void jsonRead(const QJsonObject &json);

private:
    bool            mAllowedEffectConsumption;
    bool            mAllowedEffectPollution;
    bool            mAllowedEffectProductivity;
    bool            mAllowedEffectSpeed;
    QStringList     mCraftingCategories;
    double          mCraftingSpeed;
    double          mIngredientCount;
    double          mModuleInventorySize;
    QString         mName;
};

#endif // FACTORIO_ASSEMBLER_H
