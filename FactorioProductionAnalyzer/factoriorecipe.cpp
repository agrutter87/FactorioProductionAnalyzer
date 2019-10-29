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
    /* Find "name" section in JSON object and ensure it is set to a String */
    if (json.contains("name") && json["name"].isString())
    {
        /* Set mName to value in JSON */
        mName = json["name"].toString();
    }
 }

