#ifndef PRODUCTIONCALCULATOR_H
#define PRODUCTIONCALCULATOR_H

#include <QJsonObject>
#include <QObject>

#include "factorioassembler.h"
#include "factorioitem.h"
#include "factoriominer.h"
#include "factoriomodule.h"
#include "factoriorecipe.h"
#include "factorioresource.h"

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_PRODUCTION_CALCULATOR     (0)

/*************************************************************************
 * ProductionCalculator Class
 *************************************************************************/
class ProductionCalculator
{
    Q_GADGET

public:
                                        ProductionCalculator();

    void                                setFile(QString &fileName);

    bool                                fileRead(void);
    void                                jsonRead(const QJsonObject &json);

private:
    QString mFileName;

    QVector<FactorioAssembler>          mAssemblers;
    QVector<FactorioItem>               mItems;
    QVector<FactorioMiner>              mMiners;
    QVector<FactorioModule>             mModules;
    QVector<FactorioRecipe>             mRecipes;
    QVector<FactorioResource>           mResources;
};

#endif // PRODUCTIONCALCULATOR_H
