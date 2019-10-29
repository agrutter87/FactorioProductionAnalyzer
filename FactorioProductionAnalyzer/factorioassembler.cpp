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
 * FactorioAssembler::jsonRead
 *************************************************************************/
void FactorioAssembler::jsonRead(const QJsonObject &json)
{
#if DEBUG_FACTORIO_ASSEMBLER
    qDebug() << __PRETTY_FUNCTION__;
#endif
    if (json.contains("allowed_effects"))
    {
        QJsonObject allowedEffects = json["allowed_effects"].toObject();
        if(allowedEffects.contains("consumption") && allowedEffects["consumption"].isBool())
        {
            mAllowedEffectConsumption = allowedEffects["consumption"].toBool();
        }
        if(allowedEffects.contains("pollution") && allowedEffects["pollution"].isBool())
        {
            mAllowedEffectPollution = allowedEffects["pollution"].toBool();
        }
        if(allowedEffects.contains("productivity") && allowedEffects["productivity"].isBool())
        {
            mAllowedEffectProductivity = allowedEffects["productivity"].toBool();
        }
        if(allowedEffects.contains("speed") && allowedEffects["speed"].isBool())
        {
            mAllowedEffectSpeed = allowedEffects["speed"].toBool();
        }
    }

    if(json.contains("crafting_categories") && json["crafting_categories"].isArray())
    {
        QJsonArray array = json["crafting_categories"].toArray(array);
        /* Loop through the members of the JSON array */
        for(int index = 0; index < array.size(); ++index)
        {
            mCraftingCategories.append(array[index].toString());
        }
    }

    if(json.contains("crafting_speed") && json["crafting_speed"].isDouble())
    {
        mCraftingSpeed = json["crafting_speed"].toDouble();
    }
    if(json.contains("ingredient_count") && json["ingredient_count"].isDouble())
    {
        mIngredientCount = json["ingredient_count"].toDouble();
    }
    if(json.contains("module_inventory_size") && json["module_inventory_size"].isDouble())
    {
        mModuleInventorySize = json["module_inventory_size"].toDouble();
    }

    /* Find "name" section in JSON object and ensure it is set to a String */
    if (json.contains("name") && json["name"].isString())
    {
        /* Set mName to value in JSON */
        mName = json["name"].toString();
    }
 }

