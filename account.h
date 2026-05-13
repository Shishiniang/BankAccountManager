//Page 234, chapter 6.7
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

class SavingsAccount{
    private:
        int id; //User ID
        double balance; //User balance
        double rate; //Year interest rate
        int lastDate; //Last time balance changed date
        double accumulation; //Sum of interest
        static double total;

        void record(int date,double amount);
        double accumulate(int date) const{
            return accumulation+balance*(date-lastDate);
        }

    public:
        SavingsAccount(int date,int id,double rate);
        int getId() const {return id;}
        double getBalance() const {return balance;}
        double getRate() const {return rate;}
        static double getTotal(){return total;}
        void deposit(int date, double amount);
        void withdraw(int date,double amount);
        void settle(int date);//call every Jan 1st
        void show() const;
};

#endif //__ACCOUNT_H__