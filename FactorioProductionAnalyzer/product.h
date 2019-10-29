#ifndef PRODUCT_H
#define PRODUCT_H

#include <QJsonObject>
#include <QObject>

/*************************************************************************
 * Defines
 *************************************************************************/
#define DEBUG_PRODUCT                   (0)

/*************************************************************************
 * Product Class
 *************************************************************************/
class Product
{
    Q_GADGET

public:
    typedef enum
    {
        Input                           = 0,
        Output                          = 1,
    } ProductType;

                                        Product();

    QString                             getName() const;
    void                                setName(const QString &name);

    double                              getValue() const;
    void                                setValue(double value);

    ProductType                         getProductType() const;
    void                                setProductType(ProductType productType);

    void                                jsonRead(const QJsonObject &json);
    void                                jsonWrite(QJsonObject &json) const;

    void                                print(int indentation = 0) const;

private:
    QString                             mName;
    double                              mValue;
    ProductType                         mProductType;
};

#endif // PRODUCT_H
