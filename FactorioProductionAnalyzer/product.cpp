#include "product.h"

#include <QJsonArray>

/*************************************************************************
 * Product::Product
 *************************************************************************/
Product::Product()
{
#if DEBUG_PRODUCT
    qDebug() << __PRETTY_FUNCTION__;
#endif
}

/*************************************************************************
 * Product::getName
 *************************************************************************/
QString Product::getName() const
{
#if DEBUG_PRODUCT
    qDebug() << __PRETTY_FUNCTION__;
#endif
    return mName;
}

/*************************************************************************
 * Product::setName
 *************************************************************************/
void Product::setName(const QString &name)
{
#if DEBUG_PRODUCT
    qDebug() << __PRETTY_FUNCTION__;
#endif
    mName = name;
}

/*************************************************************************
 * Product::getValue
 *************************************************************************/
double Product::getValue() const
{
#if DEBUG_PRODUCT
    qDebug() << __PRETTY_FUNCTION__;
#endif
    return mValue;
}

/*************************************************************************
 * Product::setValue
 *************************************************************************/
void Product::setValue(double value)
{
#if DEBUG_PRODUCT
    qDebug() << __PRETTY_FUNCTION__;
#endif
    mValue = value;
}

/*************************************************************************
 * Product::getProductType
 *************************************************************************/
Product::ProductType Product::getProductType() const
{
#if DEBUG_PRODUCT
    qDebug() << __PRETTY_FUNCTION__;
#endif
    return mProductType;
}

/*************************************************************************
 * Product::setProductType
 *************************************************************************/
void Product::setProductType(ProductType productType)
{
#if DEBUG_PRODUCT
    qDebug() << __PRETTY_FUNCTION__;
#endif
    mProductType = productType;
}

/*************************************************************************
 * Product::jsonRead
 *************************************************************************/
void Product::jsonRead(const QJsonObject &json)
{
#if DEBUG_PRODUCT
    qDebug() << __PRETTY_FUNCTION__;
#endif
    /* Find "name" section in JSON object and ensure it is set to a String */
    if (json.contains("name") && json["name"].isString())
    {
        /* Set mName to value in JSON */
        mName = json["name"].toString();
    }

    /* Find "value" section in JSON object and ensure it is set to a Double */
    if (json.contains("value") && json["value"].isDouble())
    {
        /* Set mValue to value in JSON */
        mValue = json["value"].toDouble();
    }
 }

/*************************************************************************
 * Product::jsonWrite
 *************************************************************************/
void Product::jsonWrite(QJsonObject &json) const
{
#if DEBUG_PRODUCT
    qDebug() << __PRETTY_FUNCTION__;
#endif
    /* Set the JSON data for "name" to mName */
    json["name"] = mName;

    /* Set the JSON data for "value" to mValue */
    json["value"] = mValue;
}
