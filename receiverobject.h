#pragma once

#include <QObject>
#include <QVariantList>

class ReceiverObject : public QObject
{
    Q_OBJECT
public:
    ReceiverObject();
    void clear();
    size_t signalsReceived() const;
    const QVariantList &results() const;

public slots:
    void sortComplete(const QVariantList &results);

private:
    QVariantList m_results;
    size_t m_signalCount{0};
};
