#include "receiverobject.h"

class Specialcases : public QObject
{
    Q_OBJECT

public:
    Specialcases();
    ~Specialcases();

private slots:
    void init();
    void emptyQList_sleepSort();
    void oneQListValue_sleepSort();
    void giantOffset_sleepSort();
    void giantOffset_sort();
    void emptyStdVector_expectInstantSignal();
    void oneStdVectorValue_expectInstantSignal();
    void twoStdVectorValues_killBeforeSignal();

private:
    static constexpr std::chrono::milliseconds s_additionalDelay{100};
    std::unique_ptr<ReceiverObject> m_testObject{std::make_unique<ReceiverObject>()};
};
