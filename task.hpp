//
// Created by marco on 6/8/16.
//

#ifndef GRAPHTHEORY_GIT_TASK_HPP
#define GRAPHTHEORY_GIT_TASK_HPP


class task
{
public:
    task();
    task(unsigned int, unsigned int, unsigned int);
    unsigned int deadline;
    unsigned int penalty;
    unsigned int number;
};


#endif //GRAPHTHEORY_GIT_TASK_HPP
