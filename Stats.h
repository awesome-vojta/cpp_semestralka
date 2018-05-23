//
// Created by vojta on 5/2/18.
//

#ifndef LESSON08_STATS_H
#define LESSON08_STATS_H


#include <utility>
#include <vector>
#include <map>
#include <fstream>
#include "Work.h"
#include "Worker.h"
#include "PrivateWork.h"
#include "CompanyWork.h"

class Stats {


private:
    vector<CompanyWork*> cws;
    vector<PrivateWork*> pws;
    vector<Worker*> workers;

    map<string, int> cwMap;
    map<string, int> pwMap;

    string working_folder = "/home/vojta/Documents/development/cpp/seme/";

    double grossProfit;


    int c;

public:

    Stats(){
        cout << "default constructor" << endl;
        c=1;
        grossProfit=0;
    }

    Stats(string file_name){
        cout << "load constructor" << endl;
        c=1;
        load(file_name);
        freqMapInit();
        grossProfit=0;
    }

    Stats(const vector<CompanyWork *> &cws, const vector<PrivateWork *> &pws, const vector<Worker *> &workers) : cws(
            cws), pws(pws), workers(workers) {
        freqMapInit();
        grossProfit=0;
        for(auto cw : cws){
            grossProfit = grossProfit + cw->getCost();
        }
        for(auto pw : pws){
            grossProfit = grossProfit + pw->getCost();
        }
    }


    /**
     * Loops through CompanyWorks and PrivateWorks
     * Creates FreqMaps for both
     */
    void freqMapInit(){
        stateDebug("freqMapInit");
        // create frequency map
        for(auto cw : cws){
            try {
                cwMap.at(cw->getName())++;
            } catch (exception& e){
                cwMap.insert(std::make_pair(cw->getName(),1));
            }
        }

        for(auto pw : pws){
            try {
                pwMap.at(pw->getName())++;
            } catch (exception& e){
                pwMap.insert(std::make_pair(pw->getName(),1));
            }
        }
    }



    /**
     * Updates :
     *          PrivateWork list
     *          pwFreqMap (if there is no PrivateWork with same name)
     *          updates grossProfit
     *
     * @param pw PrivateWork instance to be added
     */
    void addPrivateWork(PrivateWork* pw){
        stateDebug("addPrivateWork");
        pws.push_back(pw);
        try {
            pwMap.at(pw->getName())++;
        } catch (exception& e){
            pwMap.insert(std::make_pair(pw->getName(),1));
        }
        addWorker(pw->getWorker());
        grossProfit = grossProfit + pw->getCost();
    }





    /**
     * Updates :
     *          CompanyWork list
     *          cwFreqMap (if there is no CompanyWork with same name)
     *          updates grossProfit
     *
     * @param pw CompanyWork instance to be added
     */
    void addCompanyWork(CompanyWork* cw){
        stateDebug("addCompanyWork");
        cws.push_back(cw);
        try {
            cwMap.at(cw->getName())++;
        } catch (exception& e){
            cwMap.insert(std::make_pair(cw->getName(),1));
        }
        for(auto w : cw->getWorkers()){
            addWorker(w);
        }
        grossProfit = grossProfit + cw->getCost();
    }




    /**
     * Loops through ALL works, checks for name match
     * @param name Name of Work instance to be deleted
     */
    void deleteWork(string name){
        for (int i = 0; i < cws.size(); ++i) {
            if(cws.at(i)->getName()==name){
                cws.erase(cws.begin()+i);
                stateDebug("deleteWork");
                return;
            }
        }
        for (int j = 0; j < pws.size(); ++j) {
            if(pws.at(j)->getName()==name){
                pws.erase(pws.begin()+j);
                stateDebug("deleteWork");
                return;
            }
        }

    }


    /**
     * Loops through ALL workers, checks for name match
     * @param name Name of Worker instance to be deleted
     */
    // workers are identified by name for simplicity
    void deleteWorker(string name){
        for (int i = 0; i < workers.size(); ++i) {
            if(workers.at(i)->getName()==name){
                workers.erase(workers.begin()+i);
            }
        }
        stateDebug("deleteWorker");
    }







    /**
     * Adds worker to worker list
     * @param worker Worker instance
     */
    void addWorker(Worker* worker){
        Worker* w;

        // case 1: empty vector
        if(workers.size()==0){
            workers.push_back(worker);
            stateDebug("addWorker");
            return;
        }

        // case 2: worker already exists
        for (int i = 0; i < workers.size(); ++i) {
            w=workers.at(i);
            if(worker->getName()==w->getName() && worker->getMadeMoney()>0){
                // worker can be erased by new worker with same name, thats bad
                workers.at(i) = worker;
                stateDebug("addWorker");
                return;
            }
        }

        // case 3: completely new worker insertion
        workers.push_back(worker);
        stateDebug("addWorker");
        return;

    }


    vector<Worker*> getWorkers(){
        return workers;
    }









    // STATISTICS FUNCTIONS










    // what the amount this company made on their services
    void profit() {
        stateDebug("profit");
        cout << grossProfit;
    }



    /**
     * Prints basic Worker info
     * @param worker Worker instance of the worker
     */
    // how much money he made
    // in which job was he involved
    void workerInfo(Worker* worker){
        stateDebug("workerInfo");
        // iterate through all services
        // lookup if worker was involved

        // was worker involved in one of companyWorks?
        for(CompanyWork* cw : cws){
            vector<Worker*> ws = cw->getWorkers();

            for(Worker* w : ws){
                if (worker->getName() == w->getName()){
                    cout << w->getName()
                         << " was involved in " << cw->getName()
                         << " " << w->getName() << " worked for " << cw->getHours() << " long hours."
                         << " He made $" << cw->getAverageWorkerCost() << endl;
                }
            }
        }

        // was worker involved in one of privateWorks?
        for(PrivateWork* pw : pws){
            if (pw->getWorker()->getName() == worker->getName()){
                cout << worker->getName()
                     << " was involved in " << pw->getName()
                     << " " << worker->getName() << " worked for " << pw->getHours() << " long hours."
                     << " He made $" << pw->getCost() << endl;
            }
        }
        cout << worker->getName() << " worked totally for " << worker->getWorkedHours() << " hours and made $"
             << worker->getMadeMoney() << " in total" << endl << endl;
    }






    /**
     * Loops through Workers, looks for the one with most money
     * @return Worker object with most money
     */
    Worker* mostExpensiveWorker(){
        stateDebug("mostExpensiveWorker");
        Worker* mostExpensive = workers.at(0);
        for (Worker* w : workers){
            if(w->getMadeMoney()>mostExpensive->getMadeMoney()){
                mostExpensive = w;
            }
        }
        return mostExpensive;
    }







    /**
     * Loops through Workers, looks for the one with most hours
     * @return Worker object with most hours
     */
    Worker* hardestWorker(){
        stateDebug("hardestWorker");

        Worker* hardestWorker = workers.at(0);
        for(auto w : workers){
            if(w->getWorkedHours()>hardestWorker->getWorkedHours()){
                hardestWorker=w;
            }
        }
        return hardestWorker;
    }







    /**
     * Loops through FrequencyMaps, returns job that has been done least frequently
     * @return Name of the service
     */
    string leastPopularService(){
        stateDebug("leastPopularService");
        freqMapInit();

        int cmin = 1000;
        int pmin = 1000;
        string cw, pw;
        for(auto s : cwMap){
            if(cmin>s.second){
                cmin = s.second;
                cw = s.first;
            }
        }
        for(auto s : pwMap){
            if(pmin>s.second){
                pmin = s.second;
                pw = s.first;
            }
        }
        if(cmin<=pmin){
            return cw;
        }else{
            return pw;
        }
    }




    /**
     * Loops through FrequencyMaps, returns job that has been done most frequently
     * @return Name of the service
     */
    string mostPopularService(){
        stateDebug("mostPopularService");
        freqMapInit();

        int cmax = 0;
        int pmax = 0;
        string cw, pw;
        for(auto s : cwMap){
            if(cmax<s.second){
                cmax = s.second;
                cw = s.first;
            }
        }
        for(auto s : pwMap){
            if(pmax<s.second){
                pmax = s.second;
                pw = s.first;
            }
        }
        if(cmax>=pmax){
            return cw;
        }else{
            return pw;
        }
    }












    // IMPORT EXPORT FUNCTIONS



    /**
     * Saves current journal into specified file in simple comma separated format
     * @param file_name
     */
    void save(string file_name) {
        stateDebug("save");

        // export all data
        ofstream myfile;
        myfile.open (working_folder + file_name);
        string output = "";


        for(auto w : workers){
            output = output + w->type() + "," + w->getName() + "\n";
        }

        for(auto pw : pws){
            output = output + pw->type() + "," + pw->getName() + "," + to_string(pw->getPricePerHour())
                     + "," + to_string(pw->getDate()) + "," + to_string(pw->getHours()) + "," + pw->getWorker()->getName() + "\n";
        }

        for(auto cw : cws){
            output = output + cw->type() + "," + cw->getName() + "," + to_string(cw->getPricePerHour())
                     + "," + to_string(cw->getDate()) + "," + to_string(cw->getHours()) + ",(";
            for(int i = 0; i < cw->getWorkers().size(); ++i){
                output = output + cw->getWorkers().at(i)->getName() + ",";
            }
            output.pop_back();
            output = output + ")\n";
        }

        myfile << output;
        myfile.close();
    }







    /**
     * Loads saved values from specified file by passing it into parsing functions
     * @param file_name
     */
    void load(string file_name){
        stateDebug("load");

        std::ifstream infile(working_folder+file_name);
        string str,type;
        int delimiterPosition;

        while(std::getline(infile,str)){
            delimiterPosition=str.find(',');
            type = str.substr(0, delimiterPosition);
            str.erase(0, delimiterPosition+1); // delete comma included

            if(type=="worker") {
                parseWorker(str);
            }else if(type=="company"){
                parseCompanyWork(str);
            }else if(type=="private"){
                parsePrivateWork(str);
            }
        }
        for(auto cw : cws){
            grossProfit = grossProfit + cw->getCost();
        }
        for(auto pw : pws){
            grossProfit = grossProfit + pw->getCost();
        }
    }







    /**
     * Parse PrivateWork Object from text
     * Get delimiter pos and create object or modify it based on the text
     * @param str example "private,privatework,120.000000,201,11,worker"
     */
    void parsePrivateWork(string str){
        stateDebug("parsePrivateWork");

        unsigned long dPos;
        int hours,date;
        string name;
        double pricePerHour;

        // get name
        dPos = str.find(',');
        name = str.substr(0, dPos);
        str.erase(0,dPos+1);

        // get pricePerHour
        dPos = str.find(',');
        pricePerHour = stod(str.substr(0, dPos));
        str.erase(0,dPos+1);

        //get date
        dPos = str.find(',');
        date = stoi(str.substr(0, dPos));
        str.erase(0,dPos+1);

        //get hours
        dPos = str.find(',');
        hours = stoi(str.substr(0, dPos));
        str.erase(0,dPos+1);


        //get worker name
        dPos = str.find(',');
        Worker* worker = new Worker(str.substr(0, dPos));
        str.erase(0,dPos+1);

        // create new work, also adds values to the worker
        PrivateWork* pw = new PrivateWork(name,pricePerHour,date,hours,worker);

        // add worker
        this->addWorker(worker);

        // add work
        pws.push_back(pw);
    }









    /**
     * Parse CompanyWork Object from text
     * Get delimiter pos and create object or modify it based on the text
     * @param str example "company,companywork,120.000000,201,11,worker"
     */
    void parseCompanyWork(string str){
        stateDebug("parseCompanyWork");

        unsigned long dPos;
        int hours,date;
        string name;
        double pricePerHour;
        vector<Worker*> workers;

        // get name
        dPos = str.find(',');
        name = str.substr(0, dPos);
        str.erase(0,dPos+1);

        // get pricePerHour
        dPos = str.find(',');
        pricePerHour = stod(str.substr(0, dPos));
        str.erase(0,dPos+1);

        //get date
        dPos = str.find(',');
        date = stoi(str.substr(0, dPos));
        str.erase(0,dPos+1);

        //get hours
        dPos = str.find(',');
        hours = stoi(str.substr(0, dPos));
        str.erase(0,dPos+2); // delete the brace before first worker


        //get worker name
        while(true){
            if(str.find(',') != std::string::npos) {
                Worker* worker = new Worker(str.substr(0, str.find(',')));
                str.erase(0, str.find(',')+1);
                workers.push_back(worker);
            }else{
                Worker* worker = new Worker(str.substr (0, str.find(')')) );
                workers.push_back(worker);
                break;
            }
        }

        // create new work (also sets worker values)
        CompanyWork* cw = new CompanyWork(name, pricePerHour, date, hours,workers);

        // add workers
        for(auto w : workers){
            this->addWorker(w);
        }

        // add work
        cws.push_back(cw);
    }










    /**
     * Parse Worker object from text, add it to Stats
     * @param str text from which to parse them workers, example: "worker,vojta"
     */
    void parseWorker(string str){
        stateDebug("parseWorker");
        //get name
        string name;
        int delimiterPosition;
        delimiterPosition = str.find(',');
        name = str.substr(0, delimiterPosition);
        Worker* w = new Worker(name);
        workers.push_back(w);
    }







    /**
     * Debug function just for developing, prints order of function called an its name
     * prints state of Stats object (worker, pw & cw info)
     * @param func name of function
     */
    void stateDebug(string func){
        cout << ">>>>  " << c++ << "  " << func << endl;
        for(auto w : workers){
            cout << "    " <<w->getName() << " " << w->getMadeMoney() << "," << endl;
        }
        for(auto pw : pws){
            cout << "    " <<pw->getName() << ", worker: " << pw->getWorker()->getName() << pw->getHours() <<
                 "<=" << pw->getWorker()->getWorkedHours() << "," << endl;
        }
        for(auto cw : cws){
            cout << "    " << cw->getName() << ", worker: " <<cw->getWorkers().at(0)->getName() <<" "<< cw->getHours() <<
                 "<=" << cw->getWorkers().at(0)->getWorkedHours() << "," << endl;
        }
    }

};


#endif //LESSON08_STATS_H
