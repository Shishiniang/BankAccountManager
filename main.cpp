//Page 134, chapter 4.7
//4_9.cpp
#include <iostream>
#include <cmath>

class SavingsAccount{
    private:
        int id; //User ID
        double balance; //User balance
        double rate; //Year interest rate
        int lastDate; //Last time balance changed date
        double accumulation; //Sum of interest

        void record(int date,double amount);
        double accumulate(int date) const{
            return accumulation+balance*(date-lastDate);
        }

    public:
        SavingsAccount(int date,int id,double rate);
        int getId(){return id;}
        double getBalance(){return balance;}
        double getRate(){return rate;}
        void deposit(int date, double amount);
        void withdraw(int date,double amount);
        void settle(int date);
        void show();
};

SavingsAccount::SavingsAccount(int date,int id,double rate):id(id),balance(0),rate(rate),lastDate(date),accumulation(0){
    std::cout<<date<<"\t#"<<id<<" is created"<<std::endl;
}

void SavingsAccount::record(int date, double amount){
    accumulation=accumulate(date);
    lastDate=date;
    amount=floor(amount*100+0.5)/100;
    balance+=amount;
    std::cout<<date<<"\t#"<<id<<"\t"<<amount<<"\t"<<balance<<std::endl;
}

void SavingsAccount::deposit(int date,double amount){
    record(date,amount);
}

void SavingsAccount::withdraw(int date,double amount){
    if(amount>getBalance()){
        std::cout<<"Error: not enough money"<<std::endl;
    }else{
        record(date,-amount);
    }
}

void SavingsAccount::settle(int date){
    double interest=accumulate(date)*rate/365;
    if(interest!=0){
        record(date,interest);
    }
    accumulation=0;
}

void SavingsAccount::show(){
    std::cout<<"#"<<id<<"\tBalance: "<<balance;
}

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
}

