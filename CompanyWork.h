//
// Created by vojta on 5/1/18.
//

#ifndef LESSON08_COMPANYWORK_H
#define LESSON08_COMPANYWORK_H


#include <utility>
#include <vector>
#include "Work.h"
#include "Worker.h"

class CompanyWork : public Work {

private:
    vector <Worker*> workers;
public:


    CompanyWork(const string &name, double pricePerHour, int date, int hours, vector<Worker*> workers)
            : Work(name, pricePerHour, date, hours), workers(workers){
        for(auto w : workers){
            w->addHours(hours);
            w->giveMoney(pricePerHour*hours/workers.size());
            w->addWork(this);
        }
    }

    const vector<Worker*> &getWorkers() const {
        return workers;
    }


    string type() override {
        return "company";
    }

    double getAverageWorkerCost(){
        int numOfWorkers = static_cast<int>(workers.size());
        double avg = getCost() / numOfWorkers;
        return avg;
    }

};


#endif //LESSON08_COMPANYWORK_H
