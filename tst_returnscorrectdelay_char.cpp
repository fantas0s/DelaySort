#include "tst_returnscorrectdelay_char.h"
#include "DelaySort.h"

#include <QtTest>

ReturnsCorrectDelay_char::ReturnsCorrectDelay_char() {}

ReturnsCorrectDelay_char::~ReturnsCorrectDelay_char() {}

void ReturnsCorrectDelay_char::init()
{
    m_testObject = std::make_unique<ReceiverObject>();
}

void ReturnsCorrectDelay_char::fourQCharValues_waitSignal()
{
    const auto result = DelaySort::sort(QList<QChar>{'2', '1', 'a', '+'},
                                        m_testObject.get(),
                                        &ReceiverObject::sortCompleteQlQc);
    QCOMPARE(result, std::chrono::milliseconds{55});
    QTest::qWait(result + s_additionalDelay);
    QCOMPARE(m_testObject->signalsReceived(), 1);
    const auto values = m_testObject->results();
    QCOMPARE(values.size(), 4);
    QCOMPARE(values.at(0).toChar(), '+');
    QCOMPARE(values.at(1).toChar(), '1');
    QCOMPARE(values.at(2).toChar(), '2');
    QCOMPARE(values.at(3).toChar(), 'a');
}

void ReturnsCorrectDelay_char::threeChar32Values_waitSignal()
{
    const auto result = DelaySort::sort(std::vector<char32_t>{'b', '9', 'F'},
                                        m_testObject.get(),
                                        &ReceiverObject::sortCompleteSvC32);
    QCOMPARE(result, std::chrono::milliseconds{42});
    QTest::qWait(result + s_additionalDelay);
    QCOMPARE(m_testObject->signalsReceived(), 1);
    const auto values = m_testObject->results();
    QCOMPARE(values.size(), 3);
    QCOMPARE(values.at(0).value<char32_t>(), '9');
    QCOMPARE(values.at(1).value<char32_t>(), 'F');
    QCOMPARE(values.at(2).value<char32_t>(), 'b');
}
