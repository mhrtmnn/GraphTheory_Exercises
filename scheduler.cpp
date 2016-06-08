//
// Created by marco on 6/8/16.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "scheduler.hpp"

//parse a scheduling file and create data structures
int scheduler::loadSchedule()
{
    ifstream fs;
    fs.open("/home/marco/Documents/Projects/ClionProjects/GraphTheory-GIT/data/onlinetestScheduler.txt");

    string line;
    if (fs.is_open())
    {
        while (getline(fs, line))
        {
            stringstream lineStream(line);
            string deadline, penalty, taskNum;

            getline(lineStream, taskNum, ',');
            getline(lineStream, deadline, ',');
            getline(lineStream, penalty, ',');

            addTask(stoi(deadline), stoi(penalty), stoi(taskNum));
        }
    }
    else
    {
        cout << "load failed!" << endl;
        exit(-1);
    }
    return 0;
}

//add a task to the task vector
void scheduler::addTask(int d, int p, int n)
{
    tasks.push_back(task(d, p, n));
}

//calculate the minimum penalty
int scheduler::minPenalty()
{
    //sort tasks ascending penalty
    sort(tasks.begin(), tasks.end(), [](task a, task b)->bool { return a.penalty > b.penalty;});

    for(task t : tasks)
    {
        insertSorted(t);
        if(checkSanity())
        {
            //task is doable --> keep in list
            continue;
        }
        else
        {
            //task is not doable --> remove from doable list
            removeTask(t.number);
        }
    }

    return getPenalty();
}

//insert taks into deadline vec in sorted fashion
int scheduler::insertSorted(task t)
{
    if(doableTasks.size() == 0)
    {
        doableTasks.push_back(t);
        return 0;
    }

    unsigned int d = t.deadline;
    vector<task>::iterator it;

    for(it = doableTasks.begin(); it != doableTasks.end(); it++)
    {
        if(d < it->deadline)
        {
            doableTasks.insert(it, t);
            return 0;
        }
    }

    doableTasks.insert(it, t);
    return 0;
}

//check whether or not the current set of tasks is still doable within specified deadlines
// --> doableTasks U {task} is still doable
bool scheduler::checkSanity()
{
    for(unsigned long i=0, s=doableTasks.size(); i<s; i++)
    {
        if( doableTasks[i].deadline < i+1 )
        {
            return false;
        }
    }
    return true;
}

//get the summation of all tasks which are not doable in time
int scheduler::getPenalty()
{
    int p = 0;
    for(task t : tasks)
    {
        p += t.penalty;
    }

    for(task t : doableTasks)
    {
        p -= t.penalty;
    }

    return p;
}

//remove tasks from doable list, as after inclusion set is not doable anymore
int scheduler::removeTask(unsigned int taskNum)
{
    for(vector<task>::iterator it = doableTasks.begin(); it != doableTasks.end(); it++)
    {
        if(it->number == taskNum)
        {
            doableTasks.erase(it);
            return 0;
        }
    }

    return -1;
}
