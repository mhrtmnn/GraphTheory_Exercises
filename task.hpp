//
// Created by marco on 6/8/16.
//

#ifndef GRAPHTHEORY_GIT_TASK_HPP
#define GRAPHTHEORY_GIT_TASK_HPP


class task
{
public:
    task();
    task(int, int, int);
    unsigned int number;
    unsigned int deadline;
    unsigned int penalty;
};


#endif //GRAPHTHEORY_GIT_TASK_HPP
