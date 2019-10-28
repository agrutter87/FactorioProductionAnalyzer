#include "productioncalculator.h"

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

