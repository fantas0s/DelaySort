#include "tst_returnscorrectsleep_int.h"
#include "DelaySort.h"

#include <QtTest>

ReturnsCorrectSleep_int::ReturnsCorrectSleep_int() {}

ReturnsCorrectSleep_int::~ReturnsCorrectSleep_int() {}

void ReturnsCorrectSleep_int::fourStdVectorValues()
{
    const auto values = DelaySort::sleepSort(std::vector<quint8>{2, 1, 3, 1});
    QCOMPARE(values.size(), 4);
    QCOMPARE(values.at(0), 1);
    QCOMPARE(values.at(1), 1);
    QCOMPARE(values.at(2), 2);
    QCOMPARE(values.at(3), 3);
}

void ReturnsCorrectSleep_int::fourQListWithNegativeValues()
{
    const auto values = DelaySort::sleepSort(QList<qint64>{5, 0, -5, -3});
    QCOMPARE(values.size(), 4);
    QCOMPARE(values.at(0), -5);
    QCOMPARE(values.at(1), -3);
    QCOMPARE(values.at(2), 0);
    QCOMPARE(values.at(3), 5);
}
