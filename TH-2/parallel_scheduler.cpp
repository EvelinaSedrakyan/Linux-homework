#include "parallel_scheduler.h"

parallel_scheduler::parallel_scheduler(size_t capacity) : capacity(capacity), stop(false) {

    for (size_t i = 0; i < capacity; ++i) {
        threads.emplace_back(&parallel_scheduler::worker, this);
    }
}

parallel_scheduler::~parallel_scheduler() {
    stop.store(true);
    condition.notify_all();
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void parallel_scheduler::run(std::function<void()> func) {
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        task_queue.push(func);
    }
    condition.notify_one();
}

void parallel_scheduler::worker() {
    while (!stop.load()) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock, [this] { return !task_queue.empty() || stop.load(); });

            if (stop.load() && task_queue.empty()) {
                return;
            }
            task = task_queue.front();
            task_queue.pop();
        }
        task();
    }
}
