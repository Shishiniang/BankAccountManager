//Page 290, chapter 7.7
//7_10.cpp
#include "account.h"
#include <iostream>
#include <vector>

int main(){
    Date date(2008,11,1);//begin date

    //create some saving accounts
    std::vector<SavingsAccount> SavingsAccounts;
    SavingsAccounts.push_back(SavingsAccount(date,"03755217",0.015));
    SavingsAccounts.push_back(SavingsAccount(date,"02342342",0.015));
    int ns=SavingsAccounts.size();

    //create some credit accounts
    std::vector<CreditAccount> CreditAccounts;
    CreditAccounts.push_back(CreditAccount(date,"C5392394",10000,0.0005,50));
    int nc=SavingsAccounts.size();

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