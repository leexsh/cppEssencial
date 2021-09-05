//
// Created by Lenovo on 2021/9/5.
//

#ifndef CPPESSENCE_TASKPOOL_H
#define CPPESSENCE_TASKPOOL_H
#include "thread"
#include "mutex"
#include "condition_variable"
#include "list"
#include "vector"
#include "memory"
#include "iostream"

using namespace  std;

class Task {
public:
    virtual void DoIt() {
        cout<<"handle a task..."<<std::endl;
    }
    virtual ~Task() {
        cout<<"a task destructed"<<endl;
    }
};

class TaskPool final  {
public:
    TaskPool();
    ~TaskPool();
    TaskPool(const TaskPool& res) = delete;
    TaskPool& operator=(const TaskPool& res) = delete;

public:
    void init(int threadNum = 5);
    void stop();
    void addTask(Task* task);
    void removeAll();

private:
    void threadFunc();
private:
    list<shared_ptr<Task>> m_tasklist_;
    mutex   m_mutexllist_;
    condition_variable m_mycv_;
    bool m_bRunning_;
    vector<shared_ptr<thread>> m_threads_;
};

#endif //CPPESSENCE_TASKPOOL_H
