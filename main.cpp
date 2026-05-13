//Page 234, chapter 6.7
//5_11.cpp
#include "account.h"
#include <iostream>

int main(){
    //create a few accounts
    SavingsAccount sa0(1,21325302,0.015);
    SavingsAccount sa1(1,58320212,0.015);
    //some transactions
    sa0.deposit(5,5000);
    sa1.deposit(25,10000);
    sa0.deposit(45,5500);
    sa1.withdraw(60,4000);
    //after 90 days it's settle day, caculate year interest for all accounts
    sa0.settle(90);
    sa1.settle(90);
    //print info of accounts
    sa0.show();std::cout<<std::endl;
    sa1.show();std::cout<<std::endl;
    std::cout<<"Total: "<<SavingsAccount::getTotal()<<std::endl;

    return 0;
}