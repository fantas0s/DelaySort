#pragma once

#include <QtVersionChecks>
static_assert(QT_VERSION >= QT_VERSION_CHECK(6, 7, 0), "Qt version must be at least 6.7.0");

#include <QMetaObject>
#include <QTimer>
#include <QVariant>

class QMutex;

// Supported types are limited by types that can be passed into offsetFor() and toMsec()
template<typename T>
concept IntegerType = std::same_as<T, quint8> || std::same_as<T, qint8> || std::same_as<T, quint16>
                      || std::same_as<T, qint16> || std::same_as<T, quint32>
                      || std::same_as<T, qint32> || std::same_as<T, quint64>
                      || std::same_as<T, qint64>;

template<typename T>
concept CharType = std::same_as<T, char> || std::same_as<T, wchar_t> || std::same_as<T, char8_t>
                   || std::same_as<T, char16_t> || std::same_as<T, char32_t>;

class DelaySort
{
public:
    template<typename T, typename Func1>
    static inline std::chrono::milliseconds sort(
        const QList<T> &values,
        typename QtPrivate::ContextTypeForFunctor<Func1>::ContextType *receiver,
        Func1 &&slot)
    {
        return sort(std::vector<T>{values.cbegin(), values.cend()}, receiver, slot);
    }

    template<typename T, typename Func1>
    static inline std::chrono::milliseconds sort(
        const std::vector<T> &values,
        typename QtPrivate::ContextTypeForFunctor<Func1>::ContextType *receiver,
        Func1 &&slotPtr)
    {
        const auto valueCount = values.size();
        // Empty array or one value array can be returned at once
        if (values.size() < 2) {
            QVariantList results;
            if (!values.empty())
                results.append(QVariant::fromValue(values.front()));
            QMetaObject::invokeMethod(receiver,
                                      slotPtr,
                                      Qt::ConnectionType::DirectConnection,
                                      results);
            return std::chrono::milliseconds{0}; // Already called the slot
        }
        // Otherwise, run
        QVariantList *results = new QVariantList;
        bool *guard = new bool;
        *guard = true; // results has been allocated
        // When receiver is deleted, free pointer AND guard (all timer connections will be destroyed so no more calls to lambda will occur)
        QObject::connect(receiver, &QObject::destroyed, [results, guard]() {
            deletePtrs(results, guard, true);
        });
        const auto offset = offsetFor(values);
        for (const auto &value : values) {
            QTimer::singleShot(toMsec(value, offset),
                               Qt::TimerType::PreciseTimer,
                               receiver,
                               [results, guard, receiver, slotPtr, valueCount, value]() {
                                   appendToResults(*results, QVariant::fromValue(value));
                                   if (results->size() == valueCount) {
                                       QMetaObject::invokeMethod(receiver,
                                                                 slotPtr,
                                                                 Qt::ConnectionType::DirectConnection,
                                                                 *results);
                                       // All values processed, free pointer as it won't be used after this. Keep guard.
                                       deletePtrs(results, guard, false);
                                   }
                               });
        }
        return toMsec(std::ranges::max(values), offset);
    }

private:
    DelaySort() = delete;
    // automatic overload for supported types
    template<typename T>
    static T offsetFor(const QList<T> &values)
    {
        return offsetFor(std::vector<T>{values.cbegin(), values.cend()});
    }

    // Type-specific delay calculations
    template<IntegerType T>
    static T offsetFor(const std::vector<T> &values)
    {
        return std::ranges::min(values);
    }
    template<IntegerType T>
    static std::chrono::milliseconds toMsec(const T &value, const T &offset)
    {
        return std::chrono::milliseconds{value - offset + 1};
    }

    template<CharType T>
    static quint32 offsetFor(const std::vector<T> &values)
    {
        return std::ranges::min(std::vector<quint32>{values.cbegin(), values.cend()});
    }
    template<CharType T>
    static std::chrono::milliseconds toMsec(const T &value, quint32 offset)
    {
        return std::chrono::milliseconds{quint32{value} - offset + 1};
    }
    // Overloads for QChar
    static quint32 offsetFor(const std::vector<QChar> &values)
    {
        std::vector<quint32> transformed;
        std::ranges::transform(values, std::back_inserter(transformed), [](const QChar &value) {
            return value.unicode();
        });
        return offsetFor(transformed);
    }
    static std::chrono::milliseconds toMsec(const QChar &value, quint32 offset)
    {
        return toMsec(value.unicode(), offset);
    }

    // mutexed handling for thread-safety.
    static std::unique_ptr<QMutex> s_mutex;
    static void appendToResults(QVariantList &results, const QVariant &value);
    static void deletePtrs(QVariantList *results, bool *guard, bool deleteGuard);
};
