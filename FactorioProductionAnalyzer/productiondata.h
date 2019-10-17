#ifndef PRODUCTIONDATA_H
#define PRODUCTIONDATA_H

#include <QJsonObject>
#include <QObject>
#include <QVector>

#include "product.h"

/*************************************************************************
 * Defines
 *************************************************************************/

/*************************************************************************
 * ProductionData Class
 *************************************************************************/
class ProductionData
{
    Q_GADGET

public:
    ProductionData();

    int getTimestamp() const;

    QVector<Product> getInputs() const;
    void setInputs(const QVector<Product> &products);

    QVector<Product> getOutputs() const;
    void setOutputs(const QVector<Product> &products);

    void jsonRead(const QJsonObject &json);
    void jsonWrite(QJsonObject &json) const;

    void print(int indentation = 0) const;
private:
    int mTimestamp;
    QVector<Product> mInputs;
    QVector<Product> mOutputs;
};

#endif // PRODUCTIONDATA_H
