#pragma once

#include <QObject>
#include <QVariant>

class DelaySort_impl;

class DelaySort : public QObject
{
    Q_OBJECT
public:
    explicit DelaySort(QObject *parent = nullptr);
    // Integers
    std::chrono::milliseconds sort(const std::vector<quint8>& values);
    std::chrono::milliseconds sort(const std::vector<quint16>& values);
    std::chrono::milliseconds sort(const std::vector<quint32>& values);
    std::chrono::milliseconds sort(const std::vector<quint64>& values);
    std::chrono::milliseconds sort(const std::vector<qint8>& values);
    std::chrono::milliseconds sort(const std::vector<qint16>& values);
    std::chrono::milliseconds sort(const std::vector<qint32>& values);
    std::chrono::milliseconds sort(const std::vector<qint64>& values);
    std::chrono::milliseconds sort(const QList<quint8>& values);
    std::chrono::milliseconds sort(const QList<quint16>& values);
    std::chrono::milliseconds sort(const QList<quint32>& values);
    std::chrono::milliseconds sort(const QList<quint64>& values);
    std::chrono::milliseconds sort(const QList<qint8>& values);
    std::chrono::milliseconds sort(const QList<qint16>& values);
    std::chrono::milliseconds sort(const QList<qint32>& values);
    std::chrono::milliseconds sort(const QList<qint64>& values);

signals:
    void sorted(QVariantList sortedValues);

private:
    std::shared_ptr<DelaySort_impl> m_impl;
};
