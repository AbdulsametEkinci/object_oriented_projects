#include "../include/worker.hpp"
#include <string>


void Worker::increaseHeadWorkerCount(){
    m_num_head_workers++;    
}

Worker::Worker(std::string name, float cost_per_day, float base_return_per_day) : Unit(name, cost_per_day, base_return_per_day){
    m_experience = 0;
}

float Worker::getReturnPerDay(){
    m_experience++;
    if(m_experience == 10){
        increaseHeadWorkerCount();
    }
    return Unit::getReturnPerDay() + (m_experience)*2 + m_num_head_workers*3;
}
int Worker::getExperience() const{
    return m_experience;
}