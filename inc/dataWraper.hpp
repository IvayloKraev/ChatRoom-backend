#ifndef DATAWRAPER_HPP
#define DATAWRAPER_HPP

#include <queue>
#include <mutex>

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
    }

    valueT pop()
    {
        std::lock_guard<std::mutex> lock_guard(_controlerMutex);

        if(_dataQueue.empty())
        {
            return {};
        }

        valueT valueForPop = std::move(_dataQueue.front());
        _dataQueue.pop();
        return std::move(valueForPop);
    }

private:
    std::queue<valueT> _dataQueue;
    std::mutex _controlerMutex;
};

#endif
