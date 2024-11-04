#include "receiverobject.h"

#include <QVariantList>

ReceiverObject::ReceiverObject()
    : QObject{nullptr}
{}

void ReceiverObject::clear()
{
    m_results.clear();
    m_signalCount = 0;
}

size_t ReceiverObject::signalsReceived() const
{
    return m_signalCount;
}

const QVariantList &ReceiverObject::results() const
{
    return m_results;
}

void ReceiverObject::sortCompleteQlQc(const QList<QChar> &results)
{
    templatedInsert(results);
}

void ReceiverObject::sortCompleteSvC32(const std::vector<char32_t> &results)
{
    templatedInsert(results);
}

void ReceiverObject::sortCompleteSvQui8(const std::vector<quint8> &results)
{
    templatedInsert(results);
}

void ReceiverObject::sortCompleteSvQui16(const std::vector<quint16> &results)
{
    templatedInsert(results);
}

void ReceiverObject::sortCompleteSvQui64(const std::vector<quint64> &results)
{
    templatedInsert(results);
}

void ReceiverObject::sortCompleteQlQi64(const QList<qint64> &results)
{
    templatedInsert(results);
}
