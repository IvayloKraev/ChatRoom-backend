#ifndef DATAWRAPER_HPP
#define DATAWRAPER_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename valueT>
class DataWraper
{
public:
    explicit DataWraper() = default;
    ~DataWraper() = default;

    void push(valueT value)
    {
        std::lock_guard<std::mutex> lock_guard(_controlerMutex);

        _dataQueue.push(std::move(value));

        _waitForPush.notify_one();
    }

    valueT pop()
    {
        std::unique_lock<std::mutex> lock_guard(_controlerMutex);

        _waitForPush.wait(lock_guard, [&]()
        {
            return !_dataQueue.empty();
        });

        valueT valueForPop = std::move(_dataQueue.front());
        _dataQueue.pop();
        return std::move(valueForPop);
    }

private:
    std::queue<valueT> _dataQueue;
    std::mutex _controlerMutex;
    std::condition_variable _waitForPush;
};

#endif
