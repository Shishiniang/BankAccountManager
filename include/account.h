//Page 498, chapter 11.5
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "date.h"
#include "accumulator.h"
#include <string>
#include <map>
//#include<istream>//but all code uses ostream, dkw.And the reason it report no error was <iostream> has already included in date.h
#include <ostream>
#include <stdexcept>

class Account;//forward declaration
class AccountRecord{
    private:
        Date date;
        const Account* account;
        double amount;
        double balance;
        std::string desc;
    public:
        AccountRecord(const Date& date,const Account* account,double amount,double balance,const std::string& desc);
         void show()const;
};

typedef std::multimap<Date,AccountRecord>RecordMap;

class Account{
    private:
        std::string id;
        double balance;
        static double total;
        static RecordMap recordMap;
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
        //virtual void show()const;
        static void query(const Date& begin,const Date& end);//query records between begin and end
        virtual void show(std::ostream& out)const;
};
inline std::ostream& operator<<(std::ostream& out,const Account& account){
    account.show(out);
    return out; 
}

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
        void show(std::ostream& out)const;
};

class AccountException:public std::runtime_error{
private:
    const Account* account;//the account that cause the exception
public:
    AccountException(const Account* account,const std::string& msg):std::runtime_error(msg),account(account){}
    const Account* getAccount()const{return account;}
};

#endif //__ACCOUNT_H__