#ifndef FACTORIO_RECIPE_H
#define FACTORIO_RECIPE_H

#include <QJsonObject>

class FactorioRecipe
{
public:
    FactorioRecipe();

    void jsonRead(const QJsonObject &json);

private:
    QString mName;
};

#endif // FACTORIO_RECIPE_H
