//
// Created by Lenovo on 2021/9/5.
//
#include "TaskPool.h"
#include "chrono"

int main () {
    TaskPool pool;
    pool.init();
    Task* task = nullptr;
    for (int i = 0; i < 10; ++i) {
        task = new Task;
        pool.addTask(task);
    }
    this_thread::sleep_for(chrono::seconds(5));
    pool.stop();
    return 0;
}
