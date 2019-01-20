#ifndef PRODUCT_H
#define PRODUCT_H

#include <QJsonObject>
#include <QObject>

class Product
{
    Q_GADGET

public:
    typedef enum
    {
        Input,
        Output,
    } ProductType;

    Product();
    Product(const QString &name, int value);

    QString getName() const;
    void setName(const QString &name);

    double getValue() const;
    void setValue(double value);

    ProductType getProductType() const;
    void setProductType(ProductType productType);

    void jsonRead(const QJsonObject &json);
    void jsonWrite(QJsonObject &json) const;

    void print(int indentation = 0) const;
private:
    QString mName;
    double mValue;
    ProductType mProductType;
};

#endif // PRODUCT_H
