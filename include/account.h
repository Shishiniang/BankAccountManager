//Page 330, chapter 8.6
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
    public:
        const std::string &getId()const{return id;}
        double getBalance()const{return balance;}
        static double getTotal(){return total;}
        virtual void deposit(const Date& date,double amount,const std::string& desc)=0;
        virtual void withdraw(const Date& date,double amount,const std::string& desc)=0;
        virtual void settle(const Date& date)=0;
        virtual void show()const;
};
class SavingsAccount : public Account{
    private:
        Accumulator acc;
        double rate;
    public:
        SavingsAccount(const Date &date,const std::string &id,double rate);
        double getRate() const {return rate;}
        void deposit(const Date &date,double amount,const std::string &desc);
        void withdraw(const Date &date,double amount,const std::string &desc);
        void settle(const Date &date);//call every Jan 1st
};
class CreditAccount:public Account{
    private:
        Accumulator acc;
        double credit;
        double rate;
        double fee;
        double getDebt()const{
            double balance=getBalance();
            return (balance<0 ? balance:0);
        }
    public:
        CreditAccount(const Date &date,const std::string &id,double credit,double rate,double fee);
        double getCredit()const {return credit;}
        double getRate()const{return rate;}
        double getFee()const{return fee;}
        double getAvailableCredit()const{
            if(getBalance()<0){
                return credit+getBalance();
            }else{
                return credit;
            }
        }
        void deposit(const Date &date,double amount,const std::string &desc);
        void withdraw(const Date &date,double amount,const std::string &desc);
        void settle(const Date &date);
        void show()const;
};

#endif //__ACCOUNT_H__