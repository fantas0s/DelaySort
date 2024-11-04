#pragma once

#include <QChar>
#include <QList>
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
    void sortCompleteQlQc(const QList<QChar> &results);
    void sortCompleteSvC32(const std::vector<char32_t> &results);
    void sortCompleteSvQui8(const std::vector<quint8> &results);
    void sortCompleteSvQui16(const std::vector<quint16> &results);
    void sortCompleteSvQui64(const std::vector<quint64> &results);
    void sortCompleteQlQi64(const QList<qint64> &results);

private:
    template<typename ArrayT>
    void templatedInsert(const ArrayT &results)
    {
        m_results.clear();
        std::ranges::transform(results, std::back_inserter(m_results), [](const auto &value) {
            return QVariant::fromValue(value);
        });
        m_signalCount++;
    }

    QVariantList m_results;
    size_t m_signalCount{0};
};
