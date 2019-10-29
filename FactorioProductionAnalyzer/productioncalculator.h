#ifndef PRODUCTIONCALCULATOR_H
#define PRODUCTIONCALCULATOR_H

#include <QComboBox>
#include <QDialog>
#include <QHBoxLayout>
#include <QJsonObject>
#include <QLabel>
#include <QObject>
#include <QVBoxLayout>

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
    Q_OBJECT

public:
                                        ProductionCalculator(QWidget *parent = nullptr);

    void                                setFile(QString &fileName);

    bool                                fileRead(void);

private:
    void                                jsonRead(const QJsonObject &json);

    QString mFileName;

    /* Imported Data */
    QVector<FactorioAssembler>          mAssemblers;
    QVector<FactorioItem>               mItems;
    QVector<FactorioMiner>              mMiners;
    QVector<FactorioModule>             mModules;
    QVector<FactorioRecipe>             mRecipes;
    QVector<FactorioResource>           mResources;

    /* GUI elements */
    QVBoxLayout                         *mVerticalLayout;
    QHBoxLayout                         *mHorizontalLayout;

    QLabel                              *mRecipeLabel;
    QComboBox                           *mRecipeComboBox;
};

#endif // PRODUCTIONCALCULATOR_H
