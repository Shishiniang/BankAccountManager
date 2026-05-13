//Page 234, chapter 6.7
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "date.h"
#include <string>
class SavingsAccount{
    private:
        std::string id; //User ID
        double balance; //User balance
        double rate; //Year interest rate
        Date lastDate; //Last time balance changed date
        double accumulation; //Sum of interest
        static double total;

        void record(const Date &date,double amount,const std::string &desc);
        void error(const std::string &msg) const;
        double accumulate(const Date& date) const{
            return accumulation+balance*(date.distance(lastDate));
        }

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