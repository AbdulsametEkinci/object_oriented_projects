#include "factory.hpp"

Factory::Factory(float capital)
    : m_capital(capital){
    this->m_is_bankrupt = false;
}

void Factory::passOneDay(){
    float total_return = 0;
    for(auto &worker : this->m_workers){
        if(worker.getExperience() == 10){
            this->m_head_workers.push_back(worker);
        }
        total_return += worker.getReturnPerDay();
    }
    for(auto &head_worker : this->m_head_workers){
        total_return += head_worker.getReturnPerDay();
    }
    for(auto &machine : this->m_machines){
        total_return += machine.getReturnPerDay();
    }
    this->m_capital += total_return;
    if(this->m_capital < 0){
        this->m_is_bankrupt = true;
    }
    std::cout<<"[C: "<<m_capital<<", W: "<<this->getWorkerCount()<<", M: "<<this->getMachineCount()<<", HW: "<<this->getHeadWorkerCount()<<"]\n";
}

void Factory::addUnit(const Worker &rhs_worker){
    this->m_workers.push_back(rhs_worker);
    std::cout<<rhs_worker.getName()<<" is hired\n";
}
void Factory::addUnit(const Machine &rhs_machine){
    this->m_machines.push_back(rhs_machine);
    std::cout<<rhs_machine.getName()<<" is bought\n";
}

bool Factory::isBankrupt() const{
    return this->m_is_bankrupt;
}
float Factory::getCapital() const{
    return this->m_capital;
}

int Factory::getWorkerCount() const{
    return this->m_workers.size();
}
int Factory::getMachineCount() const{
    return this->m_machines.size();
}
int Factory::getHeadWorkerCount() const{
    return this->m_head_workers.size();
}