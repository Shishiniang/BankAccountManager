//Page 461, chapter 10.6
//date.h
#ifndef __DATE_H__
#define __DATE_H__

class Date{
    private:
        int year;
        int month;
        int day;
        int totalDays;
    public:
        Date():year(1970),month(1),day(1),totalDays(0){}
        Date(int year,int month,int day);
        static Date read();
        int getYear()const{return year;}
        int getMonth()const{return month;}
        int getDay()const{return day;}
        int getMaxDay()const;
        bool isLeapYear()const{
            return (year%4==0 && year%100!=0) || year%400==0;
        }
        void show()const;
        int operator-(const Date& date)const{
            return totalDays-date.totalDays;
        }
        bool operator<(const Date& date)const{
            return totalDays<date.totalDays;
        }
        bool operator<=(const Date& date)const{//different from book,dkw
            return totalDays<=date.totalDays;
        }
};

#endif