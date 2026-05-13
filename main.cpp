//Page 234, chapter 6.7
//5_11.cpp
#include "account.h"
#include <iostream>

int main(){
    Date date(2008,11,1);//begin date
    //create a few accounts
    SavingsAccount accounts[]={
        SavingsAccount(date,"03755217",0.015),
        SavingsAccount(date,"02342342",0.015)
    };
    const int n=sizeof(accounts)/sizeof(SavingsAccount);

    //some transactions in 11th month
    accounts[0].deposit(Date(2008,11,5),5000,"salary");
    accounts[1].deposit(Date(2008,11,25),10000,"sell stock 0323");
    //some transactions in 12th month
    accounts[0].deposit(Date(2008,12,5),5500,"salary");
    accounts[1].withdraw(Date(2008,12,20),4000,"buy a laptop");
    //print info of accounts
    std::cout<<std::endl;
    for(int i=0;i<n;++i){
        accounts[i].settle(Date(2009,1,1));
        accounts[i].show();
        std::cout<<std::endl;
    }
    std::cout<<"Total: "<<SavingsAccount::getTotal()<<std::endl;

    return 0;
}