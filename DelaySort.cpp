#include "DelaySort.h"

#include <QMutex>
#include <QMutexLocker>

// Static mutex
std::unique_ptr<QMutex> DelaySort::s_mutex{std::make_unique<QMutex>()};

void DelaySort::appendToResults(QVariantList &results, const QVariant &value)
{
    QMutexLocker lock(s_mutex.get());
    results.append(value);
}

void DelaySort::deletePtrs(QVariantList *results, bool *guard, bool deleteGuard)
{
    QMutexLocker lock(s_mutex.get());
    if (*guard) {
        /* Still allocated */
        delete results;
        *guard = false;
    }
    if (deleteGuard) {
        delete guard;
    }
}
