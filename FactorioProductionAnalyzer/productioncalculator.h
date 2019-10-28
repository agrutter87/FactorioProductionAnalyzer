#ifndef PRODUCTIONCALCULATOR_H
#define PRODUCTIONCALCULATOR_H

#include <QObject>

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_PRODUCTION_CALCULATOR                 (0)

/*************************************************************************
 * ProductionCalculator Class
 *************************************************************************/
class ProductionCalculator
{
    Q_GADGET

public:
    ProductionCalculator();

    void setFile(QString &fileName);

private:
    QString mFileName;
};

#endif // PRODUCTIONCALCULATOR_H
