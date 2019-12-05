#pragma once

#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <queue>

class ThreadPool {

    template <class Func, class... Args>
    void taskExec(std::promise<void> *task, Func func, Args... args) {
        task->set_value();
        delete task;
        func(args...);
    }

    template <class Promise_ptr, class Func, class... Args>
    void taskExec(Promise_ptr task, Func func, Args... args) {
        task->set_value(func(args...));
        delete task;
    }

    std::atomic<bool> check;
    size_t size;
    std::queue<std::function<void ()>> taskQueue;
    std::condition_variable newTask;
    std::vector<std::thread> threads;
    std::mutex m;

public:

    explicit ThreadPool(size_t poolSize) :
        check(true),
        size(poolSize) {
        for (size_t i = 0; i < poolSize; i++) {
            threads.emplace_back(
                [this]() {
                    while (check) {
                        std::unique_lock<std::mutex> lock(m);
                        if (taskQueue.empty()) {
                            while (check) {
                                newTask.wait(lock);
                                if (not taskQueue.empty()) {
                                    break;
                                }
                            }
                        } else {
                            auto task(std::move(taskQueue.front()));
                            taskQueue.pop();
                            lock.unlock();
                            task();
                        }
                    }
                }
            );
        }
    }

    ~ThreadPool() {
        if (check) {
            newTask.notify_all();
            for (size_t i = 0; i < size; i++) {
                threads[i].join();
            }
            check = false;
        }
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        
        auto promise = new std::promise<decltype(func(args...))>();
        auto future = promise->get_future();
        auto task = [this](std::promise<decltype(func(args...))> *promise, Func func, Args... args) {
            taskExec(promise, func, args...);
        };

        std::function<void ()> t = std::bind(task, promise, func, args...);
        m.lock();
        taskQueue.push(t);
        m.unlock();
        newTask.notify_one();
        return future;
    }
};
