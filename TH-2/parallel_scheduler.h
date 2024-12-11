#ifndef PARALLEL_SCHEDULER_H
#define PARALLEL_SCHEDULER_H

#include <thread>
#include <queue>
#include <functional>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>

class parallel_scheduler {
public:
    explicit parallel_scheduler(size_t capacity);
    ~parallel_scheduler();


    void run(std::function<void()> func);

private:

    void worker();

    size_t capacity;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> task_queue;
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};

#endif
