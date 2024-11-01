#include "receiverobject.h"

class ReturnsCorrectDelay_int : public QObject
{
    Q_OBJECT

public:
    ReturnsCorrectDelay_int();
    ~ReturnsCorrectDelay_int();

private slots:
    void init();
    void fourStdVectorValues_waitSignal();
    void fourQListWithNegativeValues_waitSignal();

private:
    static constexpr std::chrono::milliseconds s_additionalDelay{100};
    std::unique_ptr<ReceiverObject> m_testObject{std::make_unique<ReceiverObject>()};
};
