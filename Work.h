//
// Created by vojta on 5/1/18.
//

#ifndef LESSON08_WORK_H
#define LESSON08_WORK_H

#include <iostream>
#include <utility>

using namespace std;

class Work {

private:
    string name;
    double pricePerHour{};
    int date{};
    int hours{};

public:
    // std::move(object) avoids copies
    Work(string name, double pricePerHour, int date, int hours) : name(std::move(name)), pricePerHour(pricePerHour),
                                                                         date(date), hours(hours) {}
    // using list initializer


    virtual string type() = 0;


    // set as a default constructor
    Work() = default;





    // const at the end means func cannot
    // update class member
    const string &getName() const {
        return name;
    }


    double getCost(){
        double cost = hours * pricePerHour;
        return cost;
    }


    int getDate() const {
        return date;
    }




    int getHours() const {
        return hours;
    }




    void setPricePerHour(double pricePerHour) {
        Work::pricePerHour = pricePerHour;
    }




    double getPricePerHour() const {
        return pricePerHour;
    }
};


#endif //LESSON08_WORK_H
