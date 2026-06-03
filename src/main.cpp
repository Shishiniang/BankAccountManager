//Page 498, chapter 11.5
//10_24.cpp
#include "account.h"
//#include "Array.h"//replaced by STL vector
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

struct deleter{
    template<class T>
    void operator()(T* p)const{
        delete p;
    }
};//why don't just put them in deconstructor

class Controller{
private:
    Date date;
    std::vector<Account*>accounts;
    bool end;
public:
    Controller(const Date& date):date(date),end(false){}
    ~Controller();
    const Date& getDate() const{return date;}
    bool isEnd() const{return end;}
    bool runCommand(const std::string& cmdLine);
};
//oh now you don't do seperation huh? 
Controller::~Controller(){
    for_each(accounts.begin(),accounts.end(),deleter());
}
bool Controller::runCommand(const std::string& cmdLine){
    std::istringstream str(cmdLine);
    char cmd,type;
    int index,day;
    double amount,credit,rate,fee;
    std::string id,desc;
    Account* account;
    Date date1,date2;
    str>>cmd;
    switch(cmd){
        case 'a'://add account
            str>>type>>id;
            if(type=='s'){
                str>>rate;
                account=new SavingsAccount(date,id,rate);
            }else{
                str>>credit>>rate>>fee;
                account=new CreditAccount(date,id,credit,rate,fee);
            }
            accounts.push_back(account);
            return true;
        case 'd'://deposit
            str>>index>>amount;
            getline(str ,desc);
            accounts[index]->deposit(date,amount,desc);
            return true;
        case 'w'://withdraw
            str>>index>>amount;
            getline(str,desc);
            accounts[index]->withdraw(date,amount,desc);
            return true;
        case 's'://show
            for(int i=0;i<accounts.size();++i){
                std::cout<<"["<<i<<"] ";
                accounts[i]->show(std::cout);
                std::cout<<std::endl;
            }
            return false;
        case 'c'://change day
            std::cin>>day;
            if(day<date.getDay()){
                std::cout<<"You cannot specify a previous day";
            }else{
                date=Date(date.getYear(),date.getMonth()+1,1);
            }
            for(int i=0;i<accounts.size();++i){
                accounts[i]->settle(date);
            }
            return true;
        case 'n'://next month
            if(date.getMonth()==12){
                date=Date(date.getYear()+1,1,1);
            }else{
                date=Date(date.getYear(),date.getMonth()+1,1);
            }
            // for(int i=0;i<accounts.size();++i){
            //     accounts[i]->settle(date);
            // }
            for(std::vector<Account*>::iterator iter=accounts.begin();iter!=accounts.end();++iter){
                (*iter)->settle(date);
            }
            return true;
        case 'q'://query
            str>>date1>>date2;
            Account::query(date1,date2);
            return false;
        case 'e'://exit
            end=true;
            return false;
    }
    std::cout<<"Invalid command."<<std::endl;
    return false;
}


int main(){
    Date date(2008,11,1);//begin date
    Controller controller(date);
    std::string cmdLine;
    const char* FILE_NAME="commands.txt";
    std::ifstream fileIn(FILE_NAME);
    if(fileIn){
        while(std::getline(fileIn,cmdLine)){
            controller.runCommand(cmdLine);
            fileIn.close();
        }
    }

    std::ofstream fileOut(FILE_NAME,std::ios_base::app);
    std::cout<<"(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (e)exit"<<std::endl;

    //std::vector<Account*>accounts;//moved to Controller class
    while(!controller.isEnd()){
        std::cout<<controller.getDate()<<"\tTotal: "<<Account::getTotal()<<"\tCommand: ";
        std::string cmdLine;
        getline(std::cin,cmdLine);
        if(controller.runCommand(cmdLine)){
            fileOut<<cmdLine<<std::endl;
        }
    }
    return 0;
}