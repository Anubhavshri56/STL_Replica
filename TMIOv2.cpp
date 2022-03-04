#include<iostream>
#include<string.h>
#include<stdio.h>
#include<fstream>
#include<limits>
#include<ios>
using namespace std;
class fileOutputStream
{
private:
int mode;
FILE *f;
int lastOperationFailed;
public:
const static int append=1;
const static int overwrite=1;
fileOutputStream()
{
this->f=NULL;
this->lastOperationFailed=0;
this->mode=-1;
}
fileOutputStream(const char *fileName,int mode)
{
this->f=NULL;
this->mode=mode;
this->lastOperationFailed=0;
this->open(fileName,mode);
}
void open(const char *fileName,int mode)
{
if(this->f!=NULL)
{
fclose(this->f);
this->f=NULL;
this->mode=-1;
}
this->lastOperationFailed=1;
if(fileName==NULL) return;
if(mode!=append && mode!=overwrite) return;
if(mode==append) f=fopen(fileName,"a");
else if(mode==overwrite) f=fopen(fileName,"w");
if(f==NULL) return;
this->lastOperationFailed=0;
}
void close()
{
this->lastOperationFailed=0;
if(this->f==NULL) return;
fclose(this->f);
}
int fail()
{
return this->lastOperationFailed;
}
fileOutputStream & operator<<(char c)
{
this->lastOperationFailed=1;
if(this->f==NULL) return *this;
fputc(c,this->f);
this->lastOperationFailed=0;
return *this;
}
fileOutputStream & operator<<(const char *c)
{
this->lastOperationFailed=1;
if(this->f==NULL) return *this;
fputs(c,this->f);
this->lastOperationFailed=0;
return *this;
}
fileOutputStream & operator<<(string &str)
{
this->lastOperationFailed=1;
if(this->f==NULL) return *this;
fputs(str.c_str(),this->f);
this->lastOperationFailed=0;
return *this;
}
fileOutputStream & operator<<(int num)
{
char str[21];
this->lastOperationFailed=1;
if(this->f==NULL) return *this;
sprintf(str,"%d",num);
fputs(str,this->f);
this->lastOperationFailed=0;
return *this;
}
};
class fileInputStream
{
private:
int lastOperationFailed;
FILE *f;
public:
fileInputStream()
{
this->lastOperationFailed=0;
this->f=NULL;
}
fileInputStream(const char *fileName)
{
this->lastOperationFailed=0;
this->f=NULL;
this->open(fileName);
}
void open(const char *fileName)
{
this->lastOperationFailed=1;
if(this->f!=NULL)
{
fclose(this->f);
this->f=NULL;
}
if(fileName==NULL) return;
this->f=fopen(fileName,"r");
if(this->f==NULL) return;
this->lastOperationFailed=0;
}
void close()
{
this->lastOperationFailed=0;
if(this->f==NULL) return;
fclose(this->f);
}
int fail()
{
return this->lastOperationFailed;
}
fileInputStream & operator>>(char &c)
{
this->lastOperationFailed=1;
if(this->f==NULL) return *this;
if(feof(this->f)) return *this;
c=fgetc(this->f);
if(feof(this->f)) return *this;
this->lastOperationFailed=0;
return *this;
}
fileInputStream & operator>>(char *str)
{
this->lastOperationFailed=1;
if(this->f==NULL) return *this;
if(feof(this->f)) return *this;
char g;
char *p=str;
while(1)
{
g=fgetc(this->f);
if(feof(this->f) || g=='\n') break;
*p=g;
p++;
}
*p='\0';
this->lastOperationFailed=0;
return *this;
}
fileInputStream & operator>>(string &str)
{
str.clear();
this->lastOperationFailed=1;
if(this->f==NULL) return *this;
if(feof(this->f)) return *this;
char g;
while(1)
{
g=fgetc(this->f);
if(feof(this->f) || g=='\n') break;
str.push_back(g);
}
this->lastOperationFailed=0;
return *this;
}
fileInputStream & operator>>(int &num)
{
char str[21];
this->lastOperationFailed=1;
if(this->f==NULL) return *this;
if(feof(this->f)) return *this;
char g;
int x;
x=0;
while(1)
{
g=fgetc(this->f);
if(feof(this->f) || g=='\n' || g==' ') break;
str[x]=g;
x++;
}
if(x==0) return *this;
str[x]='\0';
num=atoi(str);
this->lastOperationFailed=0;
return *this;
}
};
void addStudent()
{
int rollNumber;
string name;
char gender;
cout<<"Enter roll number : ";
cin>>rollNumber;
cin.ignore(numeric_limits<streamsize>::max(),'\n');
cout<<"Enter name of student : ";
getline(cin,name);
cout<<"Enter gender : ";
cin>>gender;
fileOutputStream f("student.dat",fileOutputStream::append);
f<<rollNumber;
f<<" ";
f<<name;
f<<"\n";
f<<gender;
f.close();
}
void displayListOfStudents()
{
int rollNumber;
string name;
char gender;
fileInputStream f("student.dat");
if(f.fail())
{
cout<<"No students added"<<endl;
return;
}
while(1)
{
f>>rollNumber;
if(f.fail()) break;
f>>name;
f>>gender;
cout<<rollNumber<<" "<<name<<" "<<gender<<endl;
}
f.close();
}
int main()
{
int ch;
while(1)
{
cout<<"1. Add student\n";
cout<<"2. display List of students"<<endl;
cout<<"3. Exit"<<endl;
cout<<"Enter your choice : ";
scanf("%d",&ch);
fflush(stdin);
if(ch==1) addStudent();
else if(ch==2) displayListOfStudents();
else if(ch==3) break;
}
return 0;
}