#include "tst_returnscorrectdelay_int.h"
#include "DelaySort.h"

#include <QtTest>

ReturnsCorrectDelay_int::ReturnsCorrectDelay_int() {}

ReturnsCorrectDelay_int::~ReturnsCorrectDelay_int() {}

void ReturnsCorrectDelay_int::init()
{
    m_testObject = std::make_unique<ReceiverObject>();
}

void ReturnsCorrectDelay_int::fourStdVectorValues_waitSignal()
{
    const auto result = DelaySort::sort(std::vector<quint8>{2, 1, 3, 1},
                                        m_testObject.get(),
                                        &ReceiverObject::sortComplete);
    QCOMPARE(result, std::chrono::milliseconds{3});
    QTest::qWait(result + s_additionalDelay);
    QCOMPARE(m_testObject->signalsReceived(), 1);
    const auto values = m_testObject->results();
    QCOMPARE(values.size(), 4);
    QCOMPARE(values.at(0).toInt(), 1);
    QCOMPARE(values.at(1).toInt(), 1);
    QCOMPARE(values.at(2).toInt(), 2);
    QCOMPARE(values.at(3).toInt(), 3);
}

void ReturnsCorrectDelay_int::fourQListWithNegativeValues_waitSignal()
{
    const auto result = DelaySort::sort(QList<qint64>{5, 0, -5, -3},
                                        m_testObject.get(),
                                        &ReceiverObject::sortComplete);
    QCOMPARE(result, std::chrono::milliseconds{11});
    QTest::qWait(result + s_additionalDelay);
    QCOMPARE(m_testObject->signalsReceived(), 1);
    const auto values = m_testObject->results();
    QCOMPARE(values.size(), 4);
    QCOMPARE(values.at(0).toInt(), -5);
    QCOMPARE(values.at(1).toInt(), -3);
    QCOMPARE(values.at(2).toInt(), 0);
    QCOMPARE(values.at(3).toInt(), 5);
}
