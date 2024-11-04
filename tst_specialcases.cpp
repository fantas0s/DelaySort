#include "tst_specialcases.h"
#include "DelaySort.h"

#include <QtTest>

Specialcases::Specialcases() {}

Specialcases::~Specialcases() {}

void Specialcases::init()
{
    m_testObject = std::make_unique<ReceiverObject>();
}

void Specialcases::emptyQList_sleepSort()
{
    const auto result = DelaySort::sleepSort(QList<QChar>{});
    QCOMPARE(result.size(), 0);
}

void Specialcases::oneQListValue_sleepSort()
{
    const auto result = DelaySort::sleepSort(QList<QChar>{'f'});
    QCOMPARE(result.size(), 1);
    QCOMPARE(result.front(), QChar{'f'});
}

void Specialcases::giantOffset_sleepSort()
{
    // takes 30 seconds without offset
    const auto result = DelaySort::sleepSort(QList<int>{30005, 30000});
    QCOMPARE(result.size(), 2);
    QCOMPARE(result.front(), 30000);
    QCOMPARE(result.back(), 30005);
}

void Specialcases::giantOffset_sort()
{
    // takes 30 seconds without offset
    const auto result = DelaySort::sort(std::vector<quint64>{30005, 30000},
                                        m_testObject.get(),
                                        &ReceiverObject::sortCompleteSvQui64);
    QCOMPARE(result, std::chrono::milliseconds{6});
    QTest::qWait(result + s_additionalDelay);
    QCOMPARE(m_testObject->signalsReceived(), 1);
    const auto values = m_testObject->results();
    QCOMPARE(values.size(), 2);
    QCOMPARE(values.at(0).toInt(), 30000);
    QCOMPARE(values.at(1).toInt(), 30005);
}

void Specialcases::emptyStdVector_expectInstantSignal()
{
    const auto result = DelaySort::sort(std::vector<quint8>{},
                                        m_testObject.get(),
                                        &ReceiverObject::sortCompleteSvQui8);
    QCOMPARE(result, std::chrono::milliseconds{0});
    QCOMPARE(m_testObject->signalsReceived(), 1);
    QCOMPARE(m_testObject->results().size(), 0);
}

void Specialcases::oneStdVectorValue_expectInstantSignal()
{
    const auto result = DelaySort::sort(std::vector<quint16>{1000},
                                        m_testObject.get(),
                                        &ReceiverObject::sortCompleteSvQui16);
    QCOMPARE(result, std::chrono::milliseconds{0});
    QCOMPARE(m_testObject->signalsReceived(), 1);
    QCOMPARE(m_testObject->results().size(), 1);
    QCOMPARE(m_testObject->results().front().toInt(), 1000);
}

void Specialcases::twoStdVectorValues_killBeforeSignal()
{
    // Just verify that we don't get a crash when we deleted the object that is supposed to receive signals.
    const auto result = DelaySort::sort(std::vector<quint64>{500, 3},
                                        m_testObject.get(),
                                        &ReceiverObject::sortCompleteSvQui64);
    m_testObject.reset();
    QTest::qWait(std::chrono::seconds{1});
    QCOMPARE(result, std::chrono::milliseconds{498}); // 500 - 3 + 1
}
