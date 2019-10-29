#include "productioncalculator.h"
#include <QFile>
#include <QJsonDocument>

/*************************************************************************
 * ProductionCalculator::ProductionCalculator
 *************************************************************************/
ProductionCalculator::ProductionCalculator(QWidget *parent) : QDialog(parent)
{
#if DEBUG_PRODUCTION_CALCULATOR
    qDebug() << __PRETTY_FUNCTION__;
#endif
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
            FactorioAssembler newAssembler(object[name].toObject());
            mAssemblers.append(newAssembler);
        }
    }
    if(json.contains("items") && json["items"].isObject())
    {
        QJsonObject object = json["items"].toObject();
        foreach (QString name, object.keys())
        {
            FactorioItem newItem(object[name].toObject());
            mItems.append(newItem);
        }
    }
    if(json.contains("miners") && json["miners"].isObject())
    {
        QJsonObject object = json["miners"].toObject();
        foreach (QString name, object.keys())
        {
            FactorioMiner newMiner(object[name].toObject());
            mMiners.append(newMiner);
        }
    }
    if(json.contains("modules") && json["modules"].isObject())
    {
        QJsonObject object = json["modules"].toObject();
        foreach (QString name, object.keys())
        {
            FactorioModule newModule(object[name].toObject());
            mModules.append(newModule);
        }
    }
    if(json.contains("recipes") && json["recipes"].isObject())
    {
        QJsonObject object = json["recipes"].toObject();
        foreach (QString name, object.keys())
        {
            FactorioRecipe newRecipe(object[name].toObject());
            mRecipes.append(newRecipe);
        }
    }
    if(json.contains("resources") && json["resources"].isObject())
    {
        QJsonObject object = json["resources"].toObject();
        foreach (QString name, object.keys())
        {
            FactorioResource newResource(object[name].toObject());
            mResources.append(newResource);
        }
    }
}
