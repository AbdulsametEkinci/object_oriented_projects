#include "machine.hpp"

Machine::Machine(std::string name, float price, float cost_per_day, float base_return_per_day, float failure_probability, int repair_time, float repair_cost): Unit(name, cost_per_day, base_return_per_day){
    m_price = price;;
    m_failure_probability = failure_probability;
    m_repair_time = repair_time;
    m_repair_cost = repair_cost;
    m_days_until_repair = 0;
 }

float Machine::getReturnPerDay(){
    if(this->m_days_until_repair > 0){
        this->m_days_until_repair--;
        return -this->m_repair_cost;
    }
    else{
        if(rand() % 100 < this->m_failure_probability * 100){
            this->m_days_until_repair = this->m_repair_time;
            return -this->m_repair_cost;
        }
    return Unit::getReturnPerDay();
    }
}

float Machine::getPrice() const{
    return this->m_price;
}