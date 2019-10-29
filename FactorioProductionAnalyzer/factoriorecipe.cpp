#include "factoriorecipe.h"
#include <QJsonArray>
#include <QVector>

/*************************************************************************
 * FactorioRecipe::FactorioRecipe
 *************************************************************************/
FactorioRecipe::FactorioRecipe()
{
#if DEBUG_FACTORIO_RECIPE
    qDebug() << __PRETTY_FUNCTION__;
#endif
    mIngredients = new QVector<FactorioProduct>;
    mProducts = new QVector<FactorioProduct>;
}

/*************************************************************************
 * FactorioRecipe::FactorioRecipe
 *************************************************************************/
FactorioRecipe::FactorioRecipe(const QJsonObject &json)
{
#if DEBUG_FACTORIO_RECIPE
    qDebug() << __PRETTY_FUNCTION__;
#endif
    mIngredients = new QVector<FactorioProduct>;
    mProducts = new QVector<FactorioProduct>;
    jsonRead(json);
}

/*************************************************************************
 * FactorioRecipe::jsonRead
 *************************************************************************/
void FactorioRecipe::jsonRead(const QJsonObject &json)
{
#if DEBUG_FACTORIO_RECIPE
    qDebug() << __PRETTY_FUNCTION__;
#endif
    /* Read the category value if it exists */
    if(json.contains("category") && json["category"].isString())
    {
        mCategory = json["category"].toString();
    }

    /* Read the energy value if it exists */
    if(json.contains("energy") && json["energy"].isDouble())
    {
        mEnergy = json["energy"].toDouble();
    }

    /* Read the ingredients value if it exists */
    if(json.contains("ingredients") && json["ingredients"].isArray())
    {
        QJsonArray array = json["ingredients"].toArray(array);

        mIngredients->clear();

        mIngredients->reserve(array.size());

        /* Loop through the members of the JSON array */
        for(int index = 0; index < array.size(); ++index)
        {
            /* Create, configure, and append a new FactorioProduct */
            FactorioProduct newProduct(array[index].toObject());
            mIngredients->append(newProduct);
        }
    }

    /* Read the name value if it exists */
    if(json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }

    /* Read the products value if it exists */
    if(json.contains("products") && json["products"].isArray())
    {
        QJsonArray array = json["products"].toArray(array);

        /* Clear the existing data */
        mProducts->clear();

        /* Reserve memory for the incoming data*/
        mProducts->reserve(array.size());

        /* Loop through the members of the JSON array */
        for(int index = 0; index < array.size(); ++index)
        {
            /* Create, configure, and append a new FactorioProduct */
            FactorioProduct newProduct(array[index].toObject());
            mProducts->append(newProduct);
        }
    }
 }

