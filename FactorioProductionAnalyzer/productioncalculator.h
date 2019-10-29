#ifndef PRODUCTIONCALCULATOR_H
#define PRODUCTIONCALCULATOR_H

#include <QDialog>
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
class ProductionCalculator : public QDialog
{
    Q_GADGET

public:
                                        ProductionCalculator(QWidget *parent = nullptr);

    void                                setFile(QString &fileName);

    bool                                fileRead(void);

private:
    void                                jsonRead(const QJsonObject &json);

    QString mFileName;

    QVector<FactorioAssembler>          mAssemblers;
    QVector<FactorioItem>               mItems;
    QVector<FactorioMiner>              mMiners;
    QVector<FactorioModule>             mModules;
    QVector<FactorioRecipe>             mRecipes;
    QVector<FactorioResource>           mResources;
};

#endif // PRODUCTIONCALCULATOR_H
