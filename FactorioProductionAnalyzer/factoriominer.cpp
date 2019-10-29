#include "factoriominer.h"
#include <QJsonArray>

/*************************************************************************
 * FactorioMiner::FactorioMiner
 *************************************************************************/
FactorioMiner::FactorioMiner()
{
#if DEBUG_FACTORIO_MINER
    qDebug() << __PRETTY_FUNCTION__;
#endif
}

/*************************************************************************
 * FactorioMiner::FactorioMiner
 *************************************************************************/
FactorioMiner::FactorioMiner(const QJsonObject &json)
{
#if DEBUG_FACTORIO_MINER
    qDebug() << __PRETTY_FUNCTION__;
#endif
    jsonRead(json);
}

/*************************************************************************
 * FactorioMiner::getName
 *************************************************************************/
QString FactorioMiner::getName() const
{
#if DEBUG_FACTORIO_MINER
    qDebug() << __PRETTY_FUNCTION__;
#endif
    return mName;
}

/*************************************************************************
 * FactorioMiner::jsonRead
 *************************************************************************/
void FactorioMiner::jsonRead(const QJsonObject &json)
{
#if DEBUG_FACTORIO_MINER
    qDebug() << __PRETTY_FUNCTION__;
#endif
    /* Read the allowed_effects value if it exists */
    if (json.contains("allowed_effects"))
    {
        /* Read the allowed_effects to a separate JSON object */
        QJsonObject allowedEffects = json["allowed_effects"].toObject();

        /* Read the consumption value if it exists */
        if(allowedEffects.contains("consumption") && allowedEffects["consumption"].isBool())
        {
            mAllowedEffectConsumption = allowedEffects["consumption"].toBool();
        }

        /* Read the pollution value if it exists */
        if(allowedEffects.contains("pollution") && allowedEffects["pollution"].isBool())
        {
            mAllowedEffectPollution = allowedEffects["pollution"].toBool();
        }

        /* Read the productivity value if it exists */
        if(allowedEffects.contains("productivity") && allowedEffects["productivity"].isBool())
        {
            mAllowedEffectProductivity = allowedEffects["productivity"].toBool();
        }

        /* Read the speed value if it exists */
        if(allowedEffects.contains("speed") && allowedEffects["speed"].isBool())
        {
            mAllowedEffectSpeed = allowedEffects["speed"].toBool();
        }
    }

    /* Read the mining_speed value if it exists */
    if(json.contains("mining_speed") && json["mining_speed"].isDouble())
    {
        mMiningSpeed = json["mining_speed"].toDouble();
    }

    /* Read the name value if it exists */
    if (json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }

    /* Read the resource_categories value if it exists */
    if(json.contains("resource_categories") && json["resource_categories"].isArray())
    {
        QJsonArray array = json["resource_categories"].toArray(array);

        /* Loop through the members of the JSON array */
        for(int index = 0; index < array.size(); ++index)
        {
            mResourceCategories.append(array[index].toString());
        }
    }
}

