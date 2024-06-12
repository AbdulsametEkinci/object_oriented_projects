#include "headworker.hpp"

HeadWorker::HeadWorker(Worker &worker) : Worker(worker.getName(), worker.getCostPerDay(), worker.getReturnPerDay()){}
    
float HeadWorker::getReturnPerDay(){
    return Worker::getReturnPerDay() + Worker::getExperience()*5;
}