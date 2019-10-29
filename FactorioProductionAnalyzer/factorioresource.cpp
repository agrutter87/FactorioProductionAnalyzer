#include "factorioresource.h"
#include <QJsonArray>
#include <QVector>

/*************************************************************************
 * FactorioResource::FactorioResource
 *************************************************************************/
FactorioResource::FactorioResource()
{
#if DEBUG_FACTORIO_RESOURCE
    qDebug() << __PRETTY_FUNCTION__;
#endif
    mProducts = new QVector<FactorioProduct>;
}

/*************************************************************************
 * FactorioResource::FactorioResource
 *************************************************************************/
FactorioResource::FactorioResource(const QJsonObject &json)
{
#if DEBUG_FACTORIO_RESOURCE
    qDebug() << __PRETTY_FUNCTION__;
#endif
    jsonRead(json);
}

/*************************************************************************
 * FactorioResource::jsonRead
 *************************************************************************/
void FactorioResource::jsonRead(const QJsonObject &json)
{
#if DEBUG_FACTORIO_RESOURCE
    qDebug() << __PRETTY_FUNCTION__;
#endif
    /* Read the infinite value if it exists */
    if(json.contains("infinite") && json["infinite"].isBool())
    {
        mInfinite = json["infinite"].toBool();
    }

    /* Read the minimum value if it exists */
    if(json.contains("minimum") && json["minimum"].isDouble())
    {
        mMinimum = json["minimum"].toDouble();
    }

    /* Read the mining_time value if it exists */
    if(json.contains("mining_time") && json["mining_time"].isDouble())
    {
        mMiningTime = json["mining_time"].toDouble();
    }

    /* Read the name value if it exists */
    if (json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }

    /* Read the products value if it exists */
    if(json.contains("products") && json["products"].isArray())
    {
        QJsonArray array = json["products"].toArray(array);

        /* Loop through the members of the JSON array */
        for(int index = 0; index < array.size(); ++index)
        {
            /* Create, configure, and append a new FactorioProduct */
            FactorioProduct newProduct;
            newProduct.jsonRead(array[index].toObject());
            mProducts->append(newProduct);
        }
    }

    /* Read the resource_category value if it exists */
    if (json.contains("resource_category") && json["resource_category"].isString())
    {
        mResourceCategory = json["resource_category"].toString();
    }
}

