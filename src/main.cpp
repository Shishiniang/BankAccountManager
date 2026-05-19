//Page 290, chapter 7.7
//7_10.cpp
#include "account.h"
#include "Array.h"
#include <iostream>
#include <vector>

int main(){
    Date date(2008,11,1);//begin date

    //create some saving accounts
    Array<Account*>accounts(0);//an array of pointers that point to AbstractBaseClass that have 2 derived class
    std::cout<<"(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (e)exit"<<std::endl;

    //command processor
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
                accounts.resize(accounts.getSize()+1);//we dont have pushback or append method so...
                accounts[accounts.getSize()-1]=account;
        }
    }while(cmd!='e')


    //some transactions in 11th month
    SavingsAccounts[0].deposit(Date(2008,11,5),5000,"salary");
    CreditAccounts[0].withdraw(Date(2008,11,15),2000,"buy a cell");
    SavingsAccounts[1].deposit(Date(2008,11,25),10000,"sell stock 0323");
    //settle for credit cards
    CreditAccounts[0].settle(Date(2008,12,1));
    //some transactions in 12th month
    CreditAccounts[0].deposit(Date(2008,12,1),2016,"repay the credit");
    SavingsAccounts[1].deposit(Date(2008,12,5),5500,"salary");
    //settle for all accounts
    for(auto&& sa:SavingsAccounts){
        sa.settle((Date(2009,1,1)));
    }
    for(auto&& ca:CreditAccounts){
        ca.settle((Date(2009,1,1)));
    }
    //print info of accounts
    std::cout<<std::endl;
    for(auto&& sa:SavingsAccounts){
        sa.show();
        std::cout<<std::endl;
    }
    for(auto&& ca:CreditAccounts){
        ca.show();
        std::cout<<std::endl;
    }
    std::cout<<"Total: "<<SavingsAccount::getTotal()<<std::endl;

    return 0;
}