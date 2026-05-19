//Page 290, chapter 7.7
#include "account.h"
#include <cmath>
#include <iostream>

double Account::total=0;
Account::Account(const Date &date,const std::string &id):id(id),balance(0){
    date.show();
    std::cout<<"\t#"<<id<<" created"<<std::endl;
}
void Account::record(const Date &date,double amount,const std::string &desc){
    amount=floor(amount*100+0.5)/100;
    balance+=amount;
    total+=amount;
    date.show();
    std::cout<<"\t#"<<id<<"\t"<<amount<<"\t"<<balance<<"\t"<<desc<<std::endl;
}
void Account::show()const{
    std::cout<<id<<"\tBalance: "<<balance;
}
void Account::error(const std::string &msg)const{
    std::cout<<"Error(#"<<id<<"): "<<msg<<std::endl;
}


SavingsAccount::SavingsAccount(const Date &date,const std::string &id,double rate)
    :Account(date,id),rate(rate),acc(date,0){}

void SavingsAccount::deposit(const Date &date,double amount,const std::string &desc){
    record(date,amount,desc);
    acc.change(date,getBalance());
}

void SavingsAccount::withdraw(const Date &date,double amount,const std::string &desc){
    if(amount>getBalance()){
        error("not enough money.");
    }else{
        record(date,-amount,desc);
        acc.change(date,getBalance());
    }
}

void SavingsAccount::settle(const Date &date){
    double interest=acc.getSum(date)*rate/date.distance(Date(date.getYear()-1,1,1));
    if(interest!=0){
        record(date,interest,"Interest");
    }
    acc.reset(date,getBalance());
}

CreditAccount::CreditAccount(const Date &date,const std::string& id,double credit,double rate,double fee)
    :Account(date,id),credit(credit),rate(rate),fee(fee),acc(date,0){}

void CreditAccount::deposit(const Date &date,double amount,const std::string &desc){
    record(date,amount,desc);
    acc.change(date,getBalance());
}

void CreditAccount::withdraw(const Date &date,double amount,const std::string &desc){
    if(amount-getBalance()>credit){
        error("not enough credit.");
    }else{
        record(date,-amount,desc);
        acc.change(date,getDebt());
    }
}

void CreditAccount::settle(const Date &date){
    double interest=acc.getSum(date)*rate;
    if(interest!=0){
        record(date,interest,"Interest");
    }
    if(date.getMonth()==1){
        record(date,-fee,"Annual fee");
    }
    acc.reset(date,getDebt());
}

void CreditAccount::show()const{
    Account::show();
    std::cout<<"\tAvailable credit:"<<getAvailableCredit();
}