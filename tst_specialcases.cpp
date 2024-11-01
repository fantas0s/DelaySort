#include "tst_specialcases.h"
#include "DelaySort.h"

#include <QtTest>

Specialcases::Specialcases() {}

Specialcases::~Specialcases() {}

void Specialcases::init()
{
    m_testObject = std::make_unique<ReceiverObject>();
}

void Specialcases::emptyStdVector_expectInstantSignal()
{
    const auto result = DelaySort::sort(std::vector<quint8>{},
                                        m_testObject.get(),
                                        &ReceiverObject::sortComplete);
    QCOMPARE(result, std::chrono::milliseconds{0});
    QCOMPARE(m_testObject->signalsReceived(), 1);
    QCOMPARE(m_testObject->results().size(), 0);
}

void Specialcases::oneStdVectorValue_expectInstantSignal()
{
    const auto result = DelaySort::sort(std::vector<quint16>{1000},
                                        m_testObject.get(),
                                        &ReceiverObject::sortComplete);
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
                                        &ReceiverObject::sortComplete);
    m_testObject.reset();
    QTest::qWait(std::chrono::seconds{1});
    QCOMPARE(result, std::chrono::milliseconds{498}); // 500 - 3 + 1
}
