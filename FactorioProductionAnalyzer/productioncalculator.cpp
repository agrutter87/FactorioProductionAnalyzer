#include "productioncalculator.h"
#include <QFile>
#include <QJsonDocument>

/*************************************************************************
 * ProductionCalculator::ProductionCalculator
 *************************************************************************/
ProductionCalculator::ProductionCalculator()
{

}

/*************************************************************************
 * ProductionAnalyzer::setFile
 *************************************************************************/
void ProductionCalculator::setFile(QString &fileName)
{
#if DEBUG_PRODUCTION_CALCULATOR
    qDebug() << __PRETTY_FUNCTION__;
#endif
    mFileName = fileName;
}

/*************************************************************************
 * ProductionAnalyzer::fileRead
 *************************************************************************/
bool ProductionCalculator::fileRead(void)
{
#if DEBUG_PRODUCTION_CALCULATOR
    qDebug() << __PRETTY_FUNCTION__;
#endif
    QFile loadFile(mFileName);

    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    jsonRead(loadDoc.object());

    return true;
}

/*************************************************************************
 * ProductionAnalyzer::jsonRead
 *************************************************************************/
void ProductionCalculator::jsonRead(const QJsonObject &json)
{
#if DEBUG_PRODUCTION_CALCULATOR
    qDebug() << __PRETTY_FUNCTION__;
#endif
    if(json.contains("assemblers") && json["assemblers"].isObject())
    {
        QJsonObject object = json["assemblers"].toObject();
        foreach (QString name, object.keys())
        {
            QJsonObject assembler = object[name].toObject();
            FactorioAssembler newAssembler;
            newAssembler.jsonRead(assembler);
            mAssemblers.append(newAssembler);
        }
    }
    if(json.contains("items") && json["items"].isObject())
    {
        QJsonObject object = json["items"].toObject();
        foreach (QString name, object.keys())
        {
            QJsonObject item = object[name].toObject();
            FactorioItem newItem;
            newItem.jsonRead(item);
            mItems.append(newItem);
        }
    }
    if(json.contains("miners") && json["miners"].isObject())
    {
        QJsonObject object = json["miners"].toObject();
        foreach (QString name, object.keys())
        {
            QJsonObject miner = object[name].toObject();
            FactorioMiner newMiner;
            newMiner.jsonRead(miner);
            mMiners.append(newMiner);
        }
    }
    if(json.contains("modules") && json["modules"].isObject())
    {
        QJsonObject object = json["modules"].toObject();
        foreach (QString name, object.keys())
        {
            QJsonObject module = object[name].toObject();
            FactorioModule newModule;
            newModule.jsonRead(module);
            mModules.append(newModule);
        }
    }
    if(json.contains("recipes") && json["recipes"].isObject())
    {
        QJsonObject object = json["recipes"].toObject();
        foreach (QString name, object.keys())
        {
            QJsonObject recipe = object[name].toObject();
            FactorioRecipe newRecipe;
            newRecipe.jsonRead(recipe);
            mRecipes.append(newRecipe);
        }
    }
    if(json.contains("resources") && json["resources"].isObject())
    {
        QJsonObject object = json["resources"].toObject();
        foreach (QString name, object.keys())
        {
            QJsonObject resource = object[name].toObject();
            FactorioResource newResource;
            newResource.jsonRead(resource);
            mResources.append(newResource);
        }
    }
}
