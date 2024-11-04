#include "DelaySort.h"

// Static mutex
std::unique_ptr<QMutex> DelaySort::s_mutex{std::make_unique<QMutex>()};
