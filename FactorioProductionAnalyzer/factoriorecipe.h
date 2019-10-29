#ifndef FACTORIO_RECIPE_H
#define FACTORIO_RECIPE_H

#include <QJsonObject>
#include "factorioproduct.h"

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_FACTORIO_RECIPE           (1)

/*************************************************************************
 * FactorioRecipe Class
 *************************************************************************/
class FactorioRecipe
{
public:
                                        FactorioRecipe();

    void                                jsonRead(const QJsonObject &json);

private:
    QString                             mName;
};

#endif // FACTORIO_RECIPE_H
