//
// Created by marco on 6/8/16.
//

#ifndef GRAPHTHEORY_GIT_SCHEDULER_HPP
#define GRAPHTHEORY_GIT_SCHEDULER_HPP

#include <vector>
#include "task.hpp"

using namespace std;
class scheduler
{
public:
    void addTask(int, int, int);
    int getPenalty();
    int loadSchedule();
    int minPenalty();
    int removeTask(unsigned int);

    int insertSorted(task t);
    bool checkSanity();


private:
    vector<task> tasks;
    vector<task> doableTasks;
};


#endif //GRAPHTHEORY_GIT_SCHEDULER_HPP
