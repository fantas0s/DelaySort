#include "tst_returnscorrectdelay_char.h"
#include "tst_returnscorrectdelay_int.h"
#include "tst_returnscorrectsleep_int.h"
#include "tst_specialcases.h"

#include <QCoreApplication>
#include <QtTest>

int main(int argc, char *argv[])
{
    QCoreApplication app{argc, argv};
    int ret = 0;
    Specialcases specCaseObj;
    ret += QTest::qExec(&specCaseObj, argc, argv);
    ReturnsCorrectDelay_char charObj;
    ret += QTest::qExec(&charObj, argc, argv);
    ReturnsCorrectDelay_int intObj;
    ret += QTest::qExec(&intObj, argc, argv);
    ReturnsCorrectSleep_int sleepIntObj;
    ret += QTest::qExec(&sleepIntObj, argc, argv);
    return ret;
}
