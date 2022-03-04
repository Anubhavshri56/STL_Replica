#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>
using namespace std;
class TMDate
{
private:
int year;
int month;
int dayOfMonth;
int dayNumber;
public:
//constructors---------------------------------------------------------------------------------------------------------------------------------------------------
TMDate();
TMDate(const char *date);
TMDate(const TMDate &other);
virtual ~TMDate();
//Non Constructor methods---------------------------------------------------------------------------------------------------------------------------------
void isDateValid(const char *dateString,int *isValid,int *d,int* m,int *y);
int getMonth();
int getDayOfMonth();
int getYear();
int isLeapYear();
int getDayOfWeek();
void getMonthString(char *monthString);
void getShortMonthString(char *shortMonthString);
void getDayString(char *dayString);
void getShortDayString(char *shortDayString);
void toDayNumber();
void fromDayNumber();
int isLeapYear(int year);
//operator overLoading-----------------------------------------------------------------------------------------------------------------------------------------
void operator+=(int other);
void operator+=(TMDate &other);
void operator-=(int other);
void operator-=(TMDate &other);
int operator>(const TMDate &other);
int operator<(const TMDate &other);
int operator>=(const TMDate &other);
int operator<=(const TMDate &other);
int operator==(const TMDate &other);
int operator!=(const TMDate &other);
void operator++(int);
void operator--(int);
void operator++();
void operator--();
TMDate operator+(int days);
TMDate operator-(int days);
TMDate & operator=(const char *date);
TMDate & operator=(TMDate &other);
/*void printDayNumber()
{
cout<<this->dayNumber;
}*/
};
void TMDate::isDateValid(const char *dateString,int *isValid,int *d,int* m,int *y)
{
int x,dd,mm,yy,sepIndex1,sepIndex2,i,r;
char sep;
*isValid=0;
if(dateString==NULL) return;
x=strlen(dateString);
if(x<8 || x>10) return;
if(!(dateString[1]=='/' || dateString[2]=='/' || dateString [1]=='-' || dateString[2]=='-')) return;
if(dateString[1]=='/' || dateString[1]=='-') sepIndex1=1;
else sepIndex1=2;
sep=dateString[sepIndex1];
if(dateString[0]<48 || dateString[0]>57) return;
if(sepIndex1==2 && (dateString[1]<48 || dateString[1]>57)) return;
if(sepIndex1==1)
{
dd=dateString[0]-48;
if(dd==0) return;
}
else
{
dd=(dateString[0]-48)*10+(dateString[1]-48);
if(dd==0) return;
}
i=sepIndex1+1;
if(!(dateString[i+1]==sep || dateString[i+2]==sep)) return;
if(dateString[i+1]==sep) sepIndex2=i+1;
else sepIndex2=i+2;
if(dateString[i]<48 || dateString[i]>57) return;
if(sepIndex2==i+2 && (dateString[i+1]<48 || dateString[i+1]>57)) return;
if(sepIndex2==i+1)
{
mm=dateString[i]-48;
if(mm==0) return;
}
else
{
mm=(dateString[i]-48)*10+(dateString[i+1]-48);
if(mm==0) return;
}
yy=0;
for(r=sepIndex2+1;r<x;r++)
{
if(dateString[r]<48 || dateString[r]>57) return;
yy=yy*10+(dateString[r]-48);
}
if(yy==0) return;
*d=dd;
*m=mm;
*y=yy;
*isValid=1;
}

TMDate::TMDate()
{
time_t x;
time(&x);
struct tm *now;
now=localtime(&x);
this->year=now->tm_year+1900;
this->month=now->tm_mon+1;
this->dayOfMonth=now->tm_mday;
this->toDayNumber();
}
TMDate::TMDate(const char *date)
{
int isValid,y,m,d;
this->isDateValid(date,&isValid,&d,&m,&y);
if(isValid==0)
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
this->dayNumber=0;
}
else
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
}
TMDate::TMDate(const TMDate &other)
{
this->dayOfMonth=other.dayOfMonth;
this->month=other.month;
this->year=other.year;
this->dayNumber=other.dayNumber;
}
TMDate::~TMDate()
{
//do nothing
}
int TMDate::isLeapYear(int year)
{
if(year%400==0) return 1;
else if(year%100==0) return 0;
else if(year%4==0) return 1;
else return 0;
}
int TMDate::getMonth()
{
return this->month;
}
int TMDate::getDayOfMonth()
{
return this->dayOfMonth;
}
int TMDate::getYear()
{
return this->year;
}
void TMDate::toDayNumber()
{
int x=0;
int year=1901;
int month=0;
while(year<this->year)
{
if(isLeapYear(year)) x+=366;
else x+=365;
year++;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(year)) mth[1]=29;
int ep=this->month-2;
while(month<=ep)
{
x+=mth[month];
month++;
}
x+=this->dayOfMonth;
this->dayNumber=x;
}
void TMDate::fromDayNumber()
{
if(this->dayNumber<=0)
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
return;
}
int dNumber,d,m;
int y=1901,daysInYear,daysInMonth;
dNumber=this->dayNumber;
while(1)
{
if(isLeapYear(y)) daysInYear=366;
else daysInYear=365;
if(dNumber<=daysInYear) break;
dNumber-=daysInYear;
y++;
}
int mth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
if(isLeapYear(year)) mth[1]=29;
m=0;
while(1)
{
daysInMonth=mth[m];
if(dNumber<=daysInMonth) break;
else if(m>11) break;
dNumber-=daysInMonth;
m++;
}
m++;
d=dNumber;
this->dayOfMonth=d;
this->month=m;
this->year=y;
}
int TMDate::isLeapYear()
{
if(this->year%400==0) return 1;
else if(this->year%100==0) return 0;
else if(this->year%4==0) return 1;
else return 0;
}
int TMDate::getDayOfWeek()
{
if(this->dayNumber<=0) return 0;
int daysLeft=this->dayNumber%7+2;
if(daysLeft>7) daysLeft=daysLeft%7;
return daysLeft;
}
void TMDate::getMonthString(char *monthString)
{
if(this->dayNumber<=0)
{
*monthString='\0';
return;
}
if(this->month==1) strcpy(monthString,"January");
else if(this->month==2) strcpy(monthString,"February");
else if(this->month==3) strcpy(monthString,"March");
else if(this->month==4) strcpy(monthString,"April");
else if(this->month==5) strcpy(monthString,"May");
else if(this->month==6) strcpy(monthString,"June");
else if(this->month==7) strcpy(monthString,"July");
else if(this->month==8) strcpy(monthString,"August");
else if(this->month==9) strcpy(monthString,"September");
else if(this->month==10) strcpy(monthString,"October");
else if(this->month==11) strcpy(monthString,"November");
else strcpy(monthString,"December");
}
void TMDate::getShortMonthString(char *shortMonthString)
{
if(this->dayNumber<=0)
{
*shortMonthString='\0';
return;
}
if(this->month==1) strcpy(shortMonthString,"Jan");
else if(this->month==2) strcpy(shortMonthString,"Feb");
else if(this->month==3) strcpy(shortMonthString,"Mar");
else if(this->month==4) strcpy(shortMonthString,"Apr");
else if(this->month==5) strcpy(shortMonthString,"May");
else if(this->month==6) strcpy(shortMonthString,"Jun");
else if(this->month==7) strcpy(shortMonthString,"Jul");
else if(this->month==8) strcpy(shortMonthString,"Aug");
else if(this->month==9) strcpy(shortMonthString,"Sep");
else if(this->month==10) strcpy(shortMonthString,"Oct");
else if(this->month==11) strcpy(shortMonthString,"Nov");
else strcpy(shortMonthString,"Dec");
}
void TMDate::getDayString(char *dayString)
{
if(this->dayNumber<=0)
{
*dayString='\0';
return;
}
int day=this->getDayOfWeek();
if(day==1) strcpy(dayString,"Sunday");
else if(day==2) strcpy(dayString,"Monday");
else if(day==3) strcpy(dayString,"Tuesday");
else if(day==4) strcpy(dayString,"Wednesday");
else if(day==5) strcpy(dayString,"Thursday");
else if(day==6) strcpy(dayString,"Friday");
else strcpy(dayString,"Saturday");
}
void TMDate::getShortDayString(char *shortDayString)
{
if(this->dayNumber<=0)
{
*shortDayString='\0';
return;
}
int day=this->getDayOfWeek();
if(day==1) strcpy(shortDayString,"Sun");
else if(day==2) strcpy(shortDayString,"Mon");
else if(day==3) strcpy(shortDayString,"Tue");
else if(day==4) strcpy(shortDayString,"Wed");
else if(day==5) strcpy(shortDayString,"Thu");
else if(day==6) strcpy(shortDayString,"Fri");
else strcpy(shortDayString,"Sat");
}
void TMDate::operator+=(int other)
{
this->dayNumber+=other;
this->fromDayNumber();
}
void TMDate::operator-=(int other)
{
this->dayNumber-=other;
this->fromDayNumber();
}
void TMDate::operator+=(TMDate &other)
{
this->dayNumber+=other.dayNumber;
this->fromDayNumber();
}
void TMDate::operator-=(TMDate &other)
{
this->dayNumber-=other.dayNumber;
this->fromDayNumber();
}
int TMDate::operator>(const TMDate &other)
{
if(this->dayNumber>other.dayNumber) return 1;
else return 0;
}
int TMDate::operator<(const TMDate &other)
{
if(this->dayNumber<other.dayNumber) return 1;
else return 0;
}
int TMDate::operator>=(const TMDate &other)
{
if(this->dayNumber>=other.dayNumber) return 1;
else return 0;
}
int TMDate::operator<=(const TMDate &other)
{
if(this->dayNumber<=other.dayNumber) return 1;
else return 0;
}
int TMDate::operator==(const TMDate &other)
{
if(this->dayNumber==other.dayNumber) return 1;
else return 0;
}
int TMDate::operator!=(const TMDate &other)
{
if(this->dayNumber!=other.dayNumber) return 1;
else return 0;
}
void TMDate::operator++(int)
{
this->dayNumber++;
this->fromDayNumber();
}
void TMDate::operator++()
{
this->dayNumber++;
this->fromDayNumber();
}
void TMDate::operator--(int)
{
this->dayNumber--;
this->fromDayNumber();
}
void TMDate::operator--()
{
this->dayNumber--;
this->fromDayNumber();
}
TMDate & TMDate::operator=(const char *date)
{
int isValid,d,m,y;
this->isDateValid(date,&isValid,&d,&m,&y);
if(isValid==0)
{
this->dayOfMonth=0;
this->month=0;
this->year=0;
this->dayNumber=0;
}
else
{
this->dayOfMonth=d;
this->month=m;
this->year=y;
this->toDayNumber();
}
return *this;
}
TMDate & TMDate::operator=(TMDate &other)
{
this->dayOfMonth=other.dayOfMonth;
this->month=other.month;
this->year=other.year;
this->dayNumber=other.dayNumber;
return *this;
}
TMDate TMDate::operator+(int days)
{
if(this->dayNumber<=0) return TMDate("00/00/0000");
TMDate date;
date.dayNumber=this->dayNumber+days;
date.fromDayNumber();
return date;
}
TMDate TMDate::operator-(int days)
{
if(this->dayNumber<=0) return TMDate("00/00/0000");
TMDate date;
date.dayNumber=this->dayNumber-days;
date.fromDayNumber();
return date;
}
ostream & operator<<(ostream &oo,TMDate &tmDate)
{
oo<<tmDate.getDayOfMonth()<<"/"<<tmDate.getMonth()<<"/"<<tmDate.getYear();
return oo;
}
int main()
{
TMDate date1;
int d;
char dayName[15];
char shortDayName[15];
date1="02/04/1989";
TMDate date2="01-10-2021";
date2=date2+7;
cout<<date2<<endl;
return 0;
}