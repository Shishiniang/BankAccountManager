//Page 234, chapter 6.7
#include "account.h"
#include <cmath>
#include <iostream>

double SavingsAccount::total=0;
SavingsAccount::SavingsAccount(const Date &date,const std::string &id,double rate):id(id),balance(0),rate(rate),lastDate(date),accumulation(0){
    date.show();
    std::cout<<"\t#"<<id<<" is created"<<std::endl;
}

void SavingsAccount::record(const Date &date,double amount,const std::string &desc){
    accumulation=accumulate(date);
    lastDate=date;
    amount=floor(amount*100+0.5)/100;
    balance+=amount;
    date.show();
    std::cout<<"\t#"<<id<<"\t"<<amount<<"\t"<<balance<<std::endl;
}

void SavingsAccount::error(const std::string &msg)const{
    std::cout<<"Error(# "<<id<<"): "<<msg<<std::endl;
}

void SavingsAccount::deposit(const Date &date,double amount,const std::string &desc){
    record(date,amount,desc);
}

void SavingsAccount::withdraw(const Date &date,double amount,const std::string &desc){
    if(amount>getBalance()){
        error("not enough money.");
    }else{
        record(date,-amount,desc);
    }
}

void SavingsAccount::settle(const Date &date){
    double interest=accumulate(date)*rate/date.distance(Date(date.getYear()-1,1,1));
    if(interest!=0){
        record(date,interest,"Interest");
    }
    accumulation=0;
}

void SavingsAccount::show() const {
    std::cout<<id<<"\tBalance: "<<balance;
}