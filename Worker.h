//
// Created by vojta on 5/1/18.
//

#ifndef LESSON08_WORKER_H
#define LESSON08_WORKER_H

#include <string>
#include <vector>
#include "Work.h"

using namespace std;


class Worker {
private:
    int _id;
    string name;
    int workedHours;
    double madeMoney;
    vector<Work*> works;

public:
    Worker(string name) : name(std::move(name)){
        workedHours=0;
        madeMoney=0.0;
    }



    // '&' means func will return by reference
    const string &getName() const {
        return name;
    }


    void addHours(int hours){
        workedHours=workedHours+hours;
    }


    void giveMoney(double amount){
        madeMoney=madeMoney+amount;
    }

    void addWork(Work* work){
        works.push_back(work);
    }

    double getMadeMoney() const {
        return madeMoney;
    }

    int getWorkedHours() const {
        return workedHours;
    }

    const vector<Work *> &getWorks() const {
        return works;
    }

    string type(){
        return "worker";
    }

};


#endif //LESSON08_WORKER_H
