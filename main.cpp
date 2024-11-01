#include "tst_returnscorrectdelay_char.h"
#include "tst_returnscorrectdelay_int.h"
#include "tst_specialcases.h"

#include <QCoreApplication>
#include <QtTest>

int main(int argc, char *argv[])
{
    QCoreApplication app{argc, argv};
    Specialcases specCaseObj;
    const auto specCaseResult = QTest::qExec(&specCaseObj, argc, argv);
    ReturnsCorrectDelay_char charObj;
    const auto charResult = QTest::qExec(&charObj, argc, argv);
    ReturnsCorrectDelay_int intObj;
    const auto intResult = QTest::qExec(&intObj, argc, argv);
    return specCaseResult + charResult + intResult;
}
