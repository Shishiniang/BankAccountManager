//Page 234, chapter 6.7
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "date.h"
#include "accumulator.h"
#include <string>
class Account{
    private:
        std::string id;
        double balance;
        static double total;
    protected:
        Account(const Date &date,const std::string &id);
        void record(const Date &date,double amount,const std::string &desc);
        void error(const std::string &msg) const;
};
class SavingsAccount : public Account{
    private:
        Accumulator acc;
        double rate;
    public:
        SavingsAccount(const Date &date,const std::string &id,double rate);
        const std::string getId() const {return id;}
        double getBalance() const {return balance;}
        double getRate() const {return rate;}
        static double getTotal(){return total;}
        void deposit(const Date &date,double amount,const std::string &desc);
        void withdraw(const Date &date,double amount,const std::string &desc);
        void settle(const Date &date);//call every Jan 1st
        void show() const;
};

#endif //__ACCOUNT_H__