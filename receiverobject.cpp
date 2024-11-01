#include "receiverobject.h"

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

void ReceiverObject::sortComplete(const QVariantList &results)
{
    m_results = results;
    m_signalCount++;
}
