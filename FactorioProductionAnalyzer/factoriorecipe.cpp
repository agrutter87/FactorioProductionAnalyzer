#include "factoriorecipe.h"

/*************************************************************************
 * FactorioRecipe::FactorioRecipe
 *************************************************************************/
FactorioRecipe::FactorioRecipe()
{
#if DEBUG_FACTORIO_RECIPE
    qDebug() << __PRETTY_FUNCTION__;
#endif
}

/*************************************************************************
 * FactorioRecipe::jsonRead
 *************************************************************************/
void FactorioRecipe::jsonRead(const QJsonObject &json)
{
#if DEBUG_FACTORIO_RECIPE
    qDebug() << __PRETTY_FUNCTION__;
#endif
    /* Read the name value if it exists */
    if (json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }
 }

