#include "receiverobject.h"

class ReturnsCorrectDelay_char : public QObject
{
    Q_OBJECT

public:
    ReturnsCorrectDelay_char();
    ~ReturnsCorrectDelay_char();

private slots:
    void init();
    void fourQCharValues_waitSignal();
    void threeChar32Values_waitSignal();

private:
    static constexpr std::chrono::milliseconds s_additionalDelay{100};
    std::unique_ptr<ReceiverObject> m_testObject{std::make_unique<ReceiverObject>()};
};
