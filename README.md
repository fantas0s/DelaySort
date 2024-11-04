# DelaySort
A joke. Really.
In courtesy of: https://www.instagram.com/reel/C_DjN7WOXlk/

DelaySort class contains two "powerful" functions: ```sleepSort()``` and ```sort()```

## sleepSort()
```sleepSort()``` works like in video above: call it with an array and you will receive a sorted array.

...after a while, at least.

## sort()

sleepSort() is a blocking function so it's very boring to use it. For power-users there is non-blocking counterpart ```sort()```, which uses Qt signals to signal the result once it is available.

If you really want to try it - although I have no idea why anyone would - following code should give an insight on how it works:

```c++
#include <DelaySort.h>
#include <QObject>
/* The class that receives the signal needs to inherit QObject */
class MyClass : public QObject
{
    Q_OBJECT
protected:
    void foo()
    {
        /* This is a QList of qint16 but it could equally be std::vector and any supported type. */
        const QList<qint16> source{ -2, 5, 1, 17 };
        const auto timeUntilResultsArrive = DelaySort::sort(source, this, &MyClass::handleSortingResults);
    
        /* After timeUntilResultsArrive milliseconds the slot handleSortingResults will be called with list of sorted values.
         * The returned time is purely informative. You can just let event loop run until slot is called.
         */
    }
private slots:
    /* The slot that receives the result must match the signature of the array it passed as parameter */
    void handleSortingResults(const QList<qint16>& results)
    {
        // do something with sorted values
    }
};
```
