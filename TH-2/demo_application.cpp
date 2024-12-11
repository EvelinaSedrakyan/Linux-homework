#include <iostream>
#include <chrono>
#include "parallel_scheduler.h"

void task(int id) {
    std::cout << "Task " << id << " is being processed by thread " << std::this_thread::get_id() << std::endl;
}

int main() {

    parallel_scheduler pool(4);
    for (int i = 0; i < 10; ++i) {
        pool.run([i] { task(i); });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}
