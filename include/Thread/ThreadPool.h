#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <type_traits>

class ThreadPool {
public:
    ThreadPool(size_t threads);
    ~ThreadPool();

    // Add new work item to the pool
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        using return_type = decltype(f(args...));

        auto task = std::make_shared<std::packaged_task<return_type()> >(
            [f = std::forward<F>(f), args...]() mutable -> return_type {
                if constexpr (std::is_same_v<return_type, void>) {
                    std::invoke(f, args...);
                } else {
                    return std::invoke(f, args...);
                }
            }
        );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            if (stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");

            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return res;
    }

private:
    // Working threads
    std::vector<std::thread> workers;
    // Task queue
    std::queue<std::function<void()>> tasks;

    // Syncronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};