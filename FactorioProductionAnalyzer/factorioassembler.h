#ifndef FACTORIO_ASSEMBLER_H
#define FACTORIO_ASSEMBLER_H

#include <QJsonObject>

class FactorioAssembler
{
public:
    FactorioAssembler();

    void jsonRead(const QJsonObject &json);

private:
    QString         mName;
};

#endif // FACTORIO_ASSEMBLER_H
