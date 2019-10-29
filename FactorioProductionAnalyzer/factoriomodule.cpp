#include "factoriomodule.h"
#include <QJsonArray>

/*************************************************************************
 * FactorioModule::FactorioModule
 *************************************************************************/
FactorioModule::FactorioModule()
{
#if DEBUG_FACTORIO_MODULE
    qDebug() << __PRETTY_FUNCTION__;
#endif
}

/*************************************************************************
 * FactorioModule::FactorioModule
 *************************************************************************/
FactorioModule::FactorioModule(const QJsonObject &json)
{
#if DEBUG_FACTORIO_MODULE
    qDebug() << __PRETTY_FUNCTION__;
#endif
    jsonRead(json);
}

/*************************************************************************
 * FactorioModule::getName
 *************************************************************************/
QString FactorioModule::getName() const
{
#if DEBUG_FACTORIO_MODULE
    qDebug() << __PRETTY_FUNCTION__;
#endif
    return mName;
}

/*************************************************************************
 * FactorioModule::jsonRead
 *************************************************************************/
void FactorioModule::jsonRead(const QJsonObject &json)
{
#if DEBUG_FACTORIO_MODULE
    qDebug() << __PRETTY_FUNCTION__;
#endif

    /* Read the category value if it exists */
    if (json.contains("category") && json["category"].isString())
    {
        mCategory = json["category"].toString();
    }

    /* Read the limitations value if it exists */
    if(json.contains("limitations") && json["limitations"].isArray())
    {
        QJsonArray array = json["limitations"].toArray(array);

        /* Loop through the members of the JSON array */
        for(int index = 0; index < array.size(); ++index)
        {
            mLimitations.append(array[index].toString());
        }
    }

    /* Read the allowed_effects value if it exists */
    if (json.contains("module_effects"))
    {
        /* Read the allowed_effects to a separate JSON object */
        QJsonObject moduleEffects = json["module_effects"].toObject();

        /* Read the consumption value if it exists */
        if(moduleEffects.contains("consumption") && moduleEffects["consumption"].isBool())
        {
            mModuleEffectConsumption = moduleEffects["consumption"].toBool();
        }

        /* Read the pollution value if it exists */
        if(moduleEffects.contains("pollution") && moduleEffects["pollution"].isBool())
        {
            mModuleEffectPollution = moduleEffects["pollution"].toBool();
        }

        /* Read the productivity value if it exists */
        if(moduleEffects.contains("productivity") && moduleEffects["productivity"].isBool())
        {
            mModuleEffectProductivity = moduleEffects["productivity"].toBool();
        }

        /* Read the speed value if it exists */
        if(moduleEffects.contains("speed") && moduleEffects["speed"].isBool())
        {
            mModuleEffectSpeed = moduleEffects["speed"].toBool();
        }
    }

    /* Read the name value if it exists */
    if (json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }

    /* Read the tier value if it exists */
    if(json.contains("tier") && json["tier"].isDouble())
    {
        mTier = json["tier"].toDouble();
    }
}

