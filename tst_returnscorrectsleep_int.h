#include <QObject>

class ReturnsCorrectSleep_int : public QObject
{
    Q_OBJECT

public:
    ReturnsCorrectSleep_int();
    ~ReturnsCorrectSleep_int();

private slots:
    void fourStdVectorValues();
    void fourQListWithNegativeValues();
};
