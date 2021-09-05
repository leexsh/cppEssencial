//
// Created by Lenovo on 2021/9/5.
//

#include "TaskPool.h"
TaskPool::TaskPool() : m_bRunning_(false){
}

TaskPool::~TaskPool() {
    removeAll();
}
void TaskPool::init(int threadNum) {
    if (threadNum < 0) {
        threadNum = 5;
    }
    m_bRunning_ = true;
    for (int i = 0; i < threadNum; ++i) {
        shared_ptr<thread> spThread;
        spThread.reset(new thread(bind(&TaskPool::threadFunc, this)));
        m_threads_.push_back(spThread);
    }
}

void TaskPool::stop() {
    m_bRunning_ = false;
    m_mycv_.notify_all();
    for (auto& ite : m_threads_) {
        ite->join();
    }
}
void TaskPool::addTask(Task* task) {
    shared_ptr<Task> spTask;
    spTask.reset(task);
    {
        lock_guard<mutex> guard(m_mutexllist_);
        m_tasklist_.push_back(spTask);
        cout<<"add a task"<<endl;
    }
    m_mycv_.notify_one();
}
void TaskPool::removeAll() {
    lock_guard<mutex> guard(m_mutexllist_);
    for (auto& ite : m_tasklist_) {
        ite.reset();
    }
    m_tasklist_.clear();
}

void TaskPool::threadFunc() {
    shared_ptr<Task> spTask;
    while (true) {
        {
            unique_lock<mutex> guard(m_mutexllist_);
            while (m_tasklist_.empty()) {
                if (!m_bRunning_) {
                    break;
                }
                m_mycv_.wait(guard);
            }
            if (!m_bRunning_) {
                break;
            }
            spTask = m_tasklist_.front();
            m_tasklist_.pop_front();
        }
        if (spTask == NULL) {
            continue;
        }
        spTask->DoIt();
        spTask.reset();
    }
    cout<<"exit trhead thread id is: "<<this_thread::get_id()<<endl;
}