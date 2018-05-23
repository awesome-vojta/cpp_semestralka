#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "Work.h"
#include "Worker.h"
#include "PrivateWork.h"
#include "CompanyWork.h"
#include "Stats.h"

// Pozadavek na smysluplnou demonstraci: Work >> PrivateWork & CompanyWork
// Private: vyzaduje jednoho pracovnika
// Company: vyzaduje vice pracovniku


/**
 * Požadovaná funkcionalita:
-------------------------
1. Přidání a odebrání konkrétní nabízené činnosti.
   Změna hodinové taxy existující činnosti (v aktuální nabídce firmy).
        ->type: "pw" / "cw" to add
        ->type: "delete" to delete




2. Přidání a odebrání konkrétního zaměstance firmy.
        ->type: "w" to add
        ->type: "delete" to delete




3. Přidání záznamu o vykonané zakázce:
   - činnost, která se prováděla
   - kolik hodin to trvalo
   - seznam zaměstnanců, kteří se na činnosti podíleli
   - kdy byla zakázka realizována
     (pro jednoduchost pořadový den v roce: 1..365)
        ->type: "pw" / "cw" to add






4. Historické přehledy (za určité období v roce):
   - kolik firma celkově utržila
   - jaký zaměstnanec vykonal které činnosti a kolik celkově "stál" zákazníky
     peněz
   - činnost, která byla prováděna nejčastěji a nejméné často (nejnižší zájem)
   - zaměstnanec, který stál zákazníky nejvíce peněz
   - zaměstnanec, který pracoval na nejvíce zakázkách
           ->type: "profit" to show grossProfit



   VČETNĚ zaměstnanců, kteří u firmy již nepracují, a činností, které již
   firma v reperotáru nemá.

5. Program nabídne uživateli i možnost uložení historie do souboru a její
   možné načtení ze souboru do programu.
           ->type: "save"
           ->type: "load"


 */

int main() {
    string input;
    cout << "Welcome in Service journaling software!" << endl;
    cout << "    Controls:  'w' to create a worker (identified by name)" << endl;
    cout << "               'pw' to create a PrivateWork" << endl;
    cout << "               'cw' to create a CompanyWork (a service that requires team of workers)" << endl;
    cout << "               'load' to load already created journal" << endl;
    cout << endl;
    cout << "Once you create your journal, you can view its statistics" << endl;
    cout << "               'profit' to see gross profit" << endl;
    cout << "               'mostpopularservice' to see service that has been the most frequent" << endl;
    cout << "               'leastpopularservice' to see service that has been the least frequent" << endl;
    cout << "               'expensiveworker' to see info about most expensive worker" << endl;
    cout << "               'hardestworking' to see info about hardest working worker" << endl;
    cout << "          * type in workers name to see info about this worker" << endl;

    cout << endl;
    cout << "                'delete' to delete service or worker" << endl;
    cout << endl;
    cout << "                'save' to save this journal" << endl;
    cout << "                'q' to quit" << endl;


    Stats* stats = new Stats();

    while(true) {
        cin >> input;
        if (input == "w") {

            string name;
            cout << "name: ";
            cin >> name;
            Worker* worker = new Worker(name);
            stats->addWorker(worker);

        } else if (input == "pw") {

            string name, workerName;
            double pricePerHour;
            int date, hours;

            cout << "name: ";
            cin >> name;

            cout << "price per hour: ";
            cin >> pricePerHour;

            cout << "date: ";
            cin >> date;

            cout << "hours: ";
            cin >> hours;

            cout << "worker name: ";
            cin >> workerName;
            Worker *worker = new Worker(workerName);

            PrivateWork *privateWork = new PrivateWork(name, pricePerHour, date, hours, worker);
            stats->addPrivateWork(privateWork);

        } else if (input == "cw") {

            int num;
            string name, workerName;
            double pricePerHour;
            int date, hours;

            vector<Worker*> workers;

            cout << "name: ";
            cin >> name;

            cout << "price per hour: ";
            cin >> pricePerHour;

            cout << "date: ";
            cin >> date;

            cout << "hours: ";
            cin >> hours;

            cout << "how many workers were involved?  ";
            cin >> num;

            for (int i = 0; i < num; ++i) {
                cout << "worker name: ";
                cin >> workerName;
                Worker *worker = new Worker(workerName);
                workers.push_back(worker);
            }

            CompanyWork *companyWork = new CompanyWork(name, pricePerHour, date, hours, workers);
            stats->addCompanyWork(companyWork);

        } else if (input == "load") {
            string file_name;
            cout << "1) insert file to /home/vojta/Documents/development/cpp/seme/" << endl;
            cout << "2) enter file name: ";
            cin >> file_name;
            stats->load(file_name);

        } else if (input == "profit") {
            stats->profit();

        } else if (input == "mostpopularservice") {
            cout << stats->mostPopularService();

        } else if (input == "leastpopularservice") {
            cout << stats->leastPopularService();

        } else if (input == "expensiveworker") {
            stats->workerInfo(stats->mostExpensiveWorker());

        } else if (input == "hardestworking") {
            stats->workerInfo(stats->hardestWorker());

        } else if (input == "delete") {
            string type, name;
            cout << "service or worker? ('s' or 'w') ";
            cin >> type;
            if (type == "s") {

                cout << "name: ";
                cin >> name;
                stats->deleteWork(name);

            } else if (type == "w") {

                cout << "name: ";
                cin >> name;
                stats->deleteWorker(name);

            }
        } else if (input == "save") {
            string file_name;
            cout << "1) create a new file at /home/vojta/Documents/development/cpp/seme/" << endl;
            cout << "2) enter file name: ";
            cin >> file_name;
            stats->save(file_name);

        } else if (input == "q") {
            return 0;
        } else {
            cout << "    ERROR: 'not a valid input'";
        }
    }



    return 0;
}

