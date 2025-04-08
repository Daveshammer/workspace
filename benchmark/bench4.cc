#include "timewait.h"
#include "workspace/workspace.hpp"

int main(int argn, char** argvs) {
    int task_nums, thread_nums;
    if (argn == 3) {
        thread_nums = atoi(argvs[1]);
        task_nums = atoi(argvs[2]);
    } else {
        fprintf(stderr, "Invalid parameter! usage: [threads + tasks]\n");
        return -1;
    }

    {
        wsp::workbranch wb(thread_nums);  // 默认策略 (HighPerformance)
        auto time_cost = timewait([&] {
            auto task = [] { /* empty task */ };
            for (int i = 0; i < task_nums / 10; ++i) {
                wb.submit<wsp::task::seq>(task, task, task, task, task, task, task, task, task, task);
            }
            wb.wait_tasks();
        });
        std::cout << std::left << "Strategy: " << std::setw(15) << "HighPerformance"
                  << " | Threads: " << std::setw(2) << thread_nums << " | Tasks: " << std::setw(6) << task_nums
                  << " | Time-Cost: " << std::setw(5) << time_cost << " (s)" << std::endl;
    }

    {
        wsp::workbranch wb(thread_nums, wsp::WaitStrategy::Balanced);  // Balanced 策略
        auto time_cost = timewait([&] {
            auto task = [] { /* empty task */ };
            for (int i = 0; i < task_nums / 10; ++i) {
                wb.submit<wsp::task::seq>(task, task, task, task, task, task, task, task, task, task);
            }
            wb.wait_tasks();
        });
        std::cout << std::left << "Strategy: " << std::setw(15) << "Balanced"
                  << " | Threads: " << std::setw(2) << thread_nums << " | Tasks: " << std::setw(6) << task_nums
                  << " | Time-Cost: " << std::setw(5) << time_cost << " (s)" << std::endl;
    }

    {
        wsp::workbranch wb(thread_nums, wsp::WaitStrategy::Smooth);  // Smooth 策略
        auto time_cost = timewait([&] {
            auto task = [] { /* empty task */ };
            for (int i = 0; i < task_nums / 10; ++i) {
                wb.submit<wsp::task::seq>(task, task, task, task, task, task, task, task, task, task);
            }
            wb.wait_tasks();
        });
        std::cout << std::left << "Strategy: " << std::setw(15) << "Smooth"
                  << " | Threads: " << std::setw(2) << thread_nums << " | Tasks: " << std::setw(6) << task_nums
                  << " | Time-Cost: " << std::setw(5) << time_cost << " (s)" << std::endl;
    }
}