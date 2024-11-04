# DelaySort
A joke. Really.
In courtesy of: https://www.instagram.com/reel/C_DjN7WOXlk/

If you really want to try it, following code should give insight on how it works:

```c++
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
