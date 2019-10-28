#include "factoriorecipe.h"

/*************************************************************************
 * FactorioRecipe::FactorioRecipe
 *************************************************************************/
FactorioRecipe::FactorioRecipe()
{

}

/*************************************************************************
 * FactorioRecipe::jsonRead
 *************************************************************************/
void FactorioRecipe::jsonRead(const QJsonObject &json)
{
    /* Find "name" section in JSON object and ensure it is set to a String */
    if (json.contains("name") && json["name"].isString())
    {
        /* Set mName to value in JSON */
        mName = json["name"].toString();
    }
 }

