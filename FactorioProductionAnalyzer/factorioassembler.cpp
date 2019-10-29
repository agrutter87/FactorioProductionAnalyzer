#include "factorioassembler.h"

/*************************************************************************
 * FactorioAssembler::FactorioAssembler
 *************************************************************************/
FactorioAssembler::FactorioAssembler()
{
#if DEBUG_FACTORIO_ASSEMBLER
    qDebug() << __PRETTY_FUNCTION__;
#endif
}

/*************************************************************************
 * FactorioAssembler::FactorioAssembler
 *************************************************************************/
FactorioAssembler::FactorioAssembler(const QJsonObject &json)
{
#if DEBUG_FACTORIO_ASSEMBLER
    qDebug() << __PRETTY_FUNCTION__;
#endif
    jsonRead(json);
}

/*************************************************************************
 * FactorioAssembler::jsonRead
 *************************************************************************/
void FactorioAssembler::jsonRead(const QJsonObject &json)
{
#if DEBUG_FACTORIO_ASSEMBLER
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

    /* Read the crafting_categories value if it exists */
    if(json.contains("crafting_categories") && json["crafting_categories"].isArray())
    {
        QJsonArray array = json["crafting_categories"].toArray(array);

        /* Loop through the members of the JSON array */
        for(int index = 0; index < array.size(); ++index)
        {
            mCraftingCategories.append(array[index].toString());
        }
    }

    /* Read the crafting_speed value if it exists */
    if(json.contains("crafting_speed") && json["crafting_speed"].isDouble())
    {
        mCraftingSpeed = json["crafting_speed"].toDouble();
    }

    /* Read the ingredient_count value if it exists */
    if(json.contains("ingredient_count") && json["ingredient_count"].isDouble())
    {
        mIngredientCount = json["ingredient_count"].toDouble();
    }

    /* Read the module_inventory_size value if it exists */
    if(json.contains("module_inventory_size") && json["module_inventory_size"].isDouble())
    {
        mModuleInventorySize = json["module_inventory_size"].toDouble();
    }

    /* Read the name value if it exists */
    if (json.contains("name") && json["name"].isString())
    {
        mName = json["name"].toString();
    }
 }

