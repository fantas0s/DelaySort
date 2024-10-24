#include "DelaySort.h"

#include <QTimer>
#include <ranges>

class DelaySort_impl
{
public:
    QVariantList results;
    size_t valueCount{0};
    bool running{false};
};

namespace Sorter {
template<typename Array_T>
std::chrono::milliseconds integerSort(const Array_T &values,
                                      DelaySort *ptr,
                                      std::shared_ptr<DelaySort_impl> impl)
{
    // don't sort if already running
    if (impl->running)
        return std::chrono::milliseconds{0};

    impl->results.clear();
    impl->valueCount = values.size();
    // Empty array or one value array can be returned at once
    if (values.size() < 2) {
        if (!values.empty())
            impl->results.append(QVariant::fromValue(values.front()));
        emit ptr->sorted(impl->results);
        return std::chrono::milliseconds{1};
    }
    // Otherwise, run
    impl->running = true;
    const auto offset = std::ranges::min(values);
    for (const auto &value : values) {
        QTimer::singleShot(std::chrono::milliseconds{value - offset + 1},
                           Qt::TimerType::PreciseTimer,
                           ptr,
                           [ptr, impl, value]() {
                               impl->results.append(QVariant::fromValue(value));
                               if (impl->results.size() == impl->valueCount) {
                                   emit ptr->sorted(impl->results);
                                   impl->running = false;
                               }
                           });
    }
    return std::chrono::milliseconds{std::ranges::max(values) - offset + 1};
}
} // namespace Sorter

DelaySort::DelaySort(QObject *parent)
    : QObject{parent}
    , m_impl{std::make_shared<DelaySort_impl>()}
{}

std::chrono::milliseconds DelaySort::sort(const std::vector<quint8> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const std::vector<quint16> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const std::vector<quint32> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const std::vector<quint64> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const std::vector<qint8> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const std::vector<qint16> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const std::vector<qint32> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const std::vector<qint64> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const QList<quint8> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const QList<quint16> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const QList<quint32> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const QList<quint64> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const QList<qint8> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const QList<qint16> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const QList<qint32> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
std::chrono::milliseconds DelaySort::sort(const QList<qint64> &values)
{
    return Sorter::integerSort(values, this, m_impl);
}
