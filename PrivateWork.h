//
// Created by vojta on 5/1/18.
//

#ifndef LESSON08_PRIVATEWORK_H
#define LESSON08_PRIVATEWORK_H


#include "Work.h"

#include <utility>
#include "Worker.h"

class PrivateWork :public Work {
private:
    Worker* worker;

public:




    // std::move avoids copies
    PrivateWork(const string &name,
                double pricePerHour,
                int date,
                int hours,
                Worker* worker) : Work(name,pricePerHour,date, hours), worker(worker) {
//        cout << "adding " << hours << " to worker " << worker->getName() << endl;
        this->worker->addHours(hours);
        this->worker->giveMoney(pricePerHour * hours);
        this->worker->addWork(this);
    }


    string type() override {
        return "private";
    }

    Worker* getWorker() const {
        return worker;
    }
};


#endif //LESSON08_PRIVATEWORK_H
