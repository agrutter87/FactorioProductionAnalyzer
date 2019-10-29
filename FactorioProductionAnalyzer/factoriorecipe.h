#ifndef FACTORIO_RECIPE_H
#define FACTORIO_RECIPE_H

#include <QJsonObject>
#include "factorioproduct.h"

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_FACTORIO_RECIPE           (0)

/*************************************************************************
 * FactorioRecipe Class
 *************************************************************************/
class FactorioRecipe
{
public:
                                        FactorioRecipe();

    void                                jsonRead(const QJsonObject &json);

private:
    QString                             mCategory;
    double                              mEnergy;
    QVector<FactorioProduct>            *mIngredients;
    QString                             mName;
    QVector<FactorioProduct>            *mProducts;
};

#endif // FACTORIO_RECIPE_H
