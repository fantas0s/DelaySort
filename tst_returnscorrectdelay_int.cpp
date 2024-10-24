#include "DelaySort.h"

#include <QCoreApplication>
#include <QtTest>

class returnsCorrectDelay_int : public QObject
{
    Q_OBJECT

public:
    returnsCorrectDelay_int();
    ~returnsCorrectDelay_int();

private slots:
    void emptyStdVector_expectSignal();
    void oneStdVectorValue_expectSignal();
    void fourStdVectorValues_waitSignal();
    void twoStdVectorValues_killBeforeSignal();
    void callWhenRunning_returnsInvalid();

private:
    std::unique_ptr<DelaySort> m_testObject{std::make_unique<DelaySort>()};
};

returnsCorrectDelay_int::returnsCorrectDelay_int() {}

returnsCorrectDelay_int::~returnsCorrectDelay_int() {}

void returnsCorrectDelay_int::emptyStdVector_expectSignal()
{
    QSignalSpy sortedSpy{m_testObject.get(), &DelaySort::sorted};
    const auto result = m_testObject->sort(std::vector<quint8>{});
    QCOMPARE(result, std::chrono::milliseconds{1});
    QCOMPARE(sortedSpy.size(), 1);
    QVariantList signalParams = sortedSpy.front();
    // Only one param
    QCOMPARE(signalParams.size(), 1);
    QVariantList values = signalParams.front().toList();
    QCOMPARE(values.size(), 0);
}

void returnsCorrectDelay_int::oneStdVectorValue_expectSignal()
{
    QSignalSpy sortedSpy{m_testObject.get(), &DelaySort::sorted};
    const auto result = m_testObject->sort(std::vector<quint16>{1000});
    QCOMPARE(result, std::chrono::milliseconds{1});
    QCOMPARE(sortedSpy.size(), 1);
    QVariantList signalParams = sortedSpy.front();
    // Only one param
    QCOMPARE(signalParams.size(), 1);
    QVariantList values = signalParams.front().toList();
    QCOMPARE(values.size(), 1);
    QCOMPARE(values.front().toInt(), 1000);
}
void returnsCorrectDelay_int::fourStdVectorValues_waitSignal()
{
    QSignalSpy sortedSpy{m_testObject.get(), &DelaySort::sorted};
    const auto result = m_testObject->sort(std::vector<quint8>{2, 1, 3, 1});
    QCOMPARE(result, std::chrono::milliseconds{3}); // largest value - smallest value + 1
    QTest::qWait(result.count()+100);
    QCOMPARE(sortedSpy.size(), 1);
    QVariantList signalParams = sortedSpy.front();
    // Only one param
    QCOMPARE(signalParams.size(), 1);
    QVariantList values = signalParams.front().toList();
    QCOMPARE(values.size(), 4);
    QCOMPARE(values.at(0).toInt(), 1);
    QCOMPARE(values.at(1).toInt(), 1);
    QCOMPARE(values.at(2).toInt(), 2);
    QCOMPARE(values.at(3).toInt(), 3);
}
void returnsCorrectDelay_int::twoStdVectorValues_killBeforeSignal() {}
void returnsCorrectDelay_int::callWhenRunning_returnsInvalid() {}

QTEST_MAIN(returnsCorrectDelay_int)

#include "tst_returnscorrectdelay_int.moc"
