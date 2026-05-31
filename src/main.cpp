//Page 461, chapter 10.6
//10_24.cpp
#include "account.h"
#include "Array.h"
#include <iostream>
#include <vector>
#include <algorithm>

struct deleter{
    template<class T>
    void operator()(T* p)const{
        delete p;
    }
};

int main(){
    Date date(2008,11,1);//begin date

    //create some saving accounts
    //Array<Account*>accounts(0);//an array of pointers that point to AbstractBaseClass that have 2 derived class
    std::vector<Account*>accounts;
    std::cout<<"(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (e)exit"<<std::endl;

    //command processing loop
    char cmd;
    do{
        //show date and total
        date.show();
        std::cout<<"\tTotal: "<<Account::getTotal()<<"\tcommand>";
        char type;
        int index,day;
        double amount,credit,rate,fee;
        std::string id,desc;
        Account* account;
        //Date date1,date2; on book but not used, dkw
        std::cin>>cmd;
        switch(cmd){
            case 'a'://add account
                std::cin>>type>>id;
                if(type=='s'){
                    std::cin>>rate;
                    account=new SavingsAccount(date,id,rate);
                }else{
                    std::cin>>credit>>rate>>fee;
                    account=new CreditAccount(date,id,credit,rate,fee);
                }
                accounts.push_back(account);
                break;
            case 'd'://deposit
                std::cin>>index>>amount;
                getline(std::cin,desc);
                accounts[index]->deposit(date,amount,desc);
                break;
            case 'w'://withdraw
                std::cin>>index>>amount;
                getline(std::cin,desc);
                accounts[index]->withdraw(date,amount,desc);
                break;
            case 's'://show
                for(int i=0;i<accounts.size();++i){
                    std::cout<<"["<<i<<"] ";
                    accounts[i]->show();
                    std::cout<<std::endl;
                }
                break;
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
                break;
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
                break;
        }
    }while(cmd!='e');
    // for(int i=0;i<accounts.getSize();++i){
    //     delete accounts[i];
    // }
    for_each(accounts.begin(),accounts.end(),deleter());

    return 0;
}