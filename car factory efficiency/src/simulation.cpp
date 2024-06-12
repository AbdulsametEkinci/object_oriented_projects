#include <iostream>
#include <fstream>
#include <string>

#include "simulation.hpp"


void Simulation::printWelcomeMessage() const
{
    std::cout << "Welcome to the Car Factory!" << std::endl;
    std::cout << "You have " << m_total_days << " days to make as much money as possible" << std::endl;
    std::cout << "You can add workers, machines, and fast forward days" << std::endl;

    std::cout << "Available commands:" << std::endl;
    std::cout << "    wX: adds X workers" << std::endl;
    std::cout << "    mX: adds X machines" << std::endl;
    std::cout << "    pX: passes X days" << std::endl;
    std::cout << "    q: exit the game properly" << std::endl;
}

Machine Simulation::buyRandomMachine(){
    return m_machines_market[rand() % m_machines_market.size()];
}

Worker Simulation::hireRandomWorker(){
    return m_labor_market[rand() % m_labor_market.size()];
}

Simulation::Simulation(Factory &factory, int total_days, std::string workers_list_path, std::string machines_list_path){
    m_factory = &factory;
    m_total_days = total_days;
    
    std::ifstream workersFile(workers_list_path);
    if(workersFile.fail()){
        std::cout << "Error opening file" << std::endl;
        exit(1);
    }
    std::string line;
    std::getline(workersFile, line);
    while (!workersFile.eof()){
        std::getline(workersFile, line,' ');
        std::string name = line;
        if (!line.empty()){
            std::getline(workersFile, line, ' ');
            float dailyCost = stof(line);
            std::getline(workersFile, line);
            float dailyReturn = stof(line);
            m_labor_market.push_back(Worker(name,dailyCost,dailyReturn));
        }
    }

    // Read machines list

    std::ifstream machinesFile(machines_list_path);
    if(machinesFile.fail()){
        std::cout << "Error opening file" << std::endl;
        exit(1);
    }
    std::getline(machinesFile, line);
    while (!machinesFile.eof()){
        std::getline(machinesFile, line,' ');
        if (!line.empty()){
            std::string name = line;
            std::getline(machinesFile, line, ' ');
            float price = stof(line);
            std::getline(machinesFile, line, ' ');
            float dailyCost = stof(line);
            std::getline(machinesFile, line, ' ');
            float daily_return = stof(line);
            std::getline(machinesFile, line, ' ');
            float fail_prob = stof(line);
            std::getline(machinesFile, line, ' ');
            float repair_cost = stof(line);
            std::getline(machinesFile, line);
            int repair_time  = stoi(line);
            m_machines_market.push_back(Machine(name,price,dailyCost,daily_return,fail_prob,repair_time,repair_cost));
        }
        
    }
    
}

void Simulation::run(){
    
    std::string input;
    std::cout << "Enter command: ";
    std::cin >> input;
    int current_Day = 1;
    int total_profit=0;
    while (input != "q" && current_Day <= m_total_days && !m_factory->isBankrupt()){
        if (input[0] == 'w'){
            int numWorkers = stoi(input.substr(1));
            for (int i = 0; i < numWorkers; i++){
                m_factory->addUnit(hireRandomWorker());
            }
        }
        else if (input[0] == 'm'){
            int numMachines = stoi(input.substr(1));
            for (int i = 0; i < numMachines; i++){
                m_factory->addUnit(buyRandomMachine());
            }
        }
        else if (input[0] == 'p'){
            int numDays = stoi(input.substr(1));
            int i = 0;
            while (i < numDays && !m_factory->isBankrupt() && current_Day <= m_total_days){
                std::cout<<"---Day"<<current_Day<<"\n";
                m_factory->passOneDay();
                current_Day++;
                i++;
            }
        }
        else{
            std::cout << "Invalid command" <<"/n";
        }
        std::cout << "Enter command: ";
        std::cin >> input;
    } 
    if(input == "q"){
        std::cout << "Congrats! You have earned "<< total_profit <<
        " in "<< m_total_days  <<" days" << std::endl;
    }
    else if (current_Day > m_total_days){
        std::cout << "You have run out of days" << std::endl;
    }
    
}