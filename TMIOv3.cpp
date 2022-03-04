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
const static int overwrite=2;
const static int binary=4;
fileOutputStream()
{
this->f=NULL;
this->lastOperationFailed=0;
this->mode=-1;
}
fileOutputStream(const char *fileName,int mode)
{
this->f=NULL;
this->mode=-1;
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
if(mode!=append && mode!=overwrite && mode!=(append | binary) && mode!=(overwrite | binary)) return;
if(mode==append) this->f=fopen(fileName,"a");
else if(mode==overwrite) this->f=fopen(fileName,"w");
else if(mode==(append | binary)) this->f=fopen(fileName,"ab");
else if(mode==(overwrite | binary)) this->f=fopen(fileName,"wb");
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
void write(const char *file,int size)
{
this->lastOperationFailed=1;
if(this->f==NULL) return;
fwrite(file,size,1,this->f);
this->lastOperationFailed=0;
}
}	;
class fileInputStream
{
private:
int mode;
int lastOperationFailed;
FILE *f;
public:
const static int binary=4;
const static int reading=1;
fileInputStream()
{
this->mode=1;
this->lastOperationFailed=0;
this->f=NULL;
}
fileInputStream(const char *fileName)
{
this->mode=1;
this->lastOperationFailed=0;
this->f=NULL;
this->open(fileName,this->mode);
}
fileInputStream(const char *fileName,int mode)
{
this->mode=mode;
this->lastOperationFailed=0;
this->f=NULL;
this->open(fileName,mode);
}
void open(const char *fileName,int mode)
{
this->lastOperationFailed=1;
if(this->f!=NULL)
{
fclose(this->f);
this->f=NULL;
}
if(fileName==NULL) return;
if(mode!=reading && mode!=binary) return;
if(mode==reading) this->f=fopen(fileName,"r");
else if(mode==binary) this->f=fopen(fileName,"rb");
if(this->f==NULL) return;
this->mode=mode;
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
void read(char *file,int size)
{
this->lastOperationFailed=1;
if(this->f==NULL) return;
if(feof(this->f)) return;
fread(file,size,1,this->f);
if(feof(this->f)) return;
this->lastOperationFailed=0;
}
};
class student
{
private:
int rollNumber;
char name[32];
public:
void setRollNumber(int rollNumber)
{
this->rollNumber=rollNumber;
}
int getRollNumber()
{
return this->rollNumber;
}
void setName(const char *name)
{
strcpy(this->name,name);
}
void getName(char *name)
{
strcpy(name,this->name);
}
};
void addStudent()
{
int rollNumber;
string name;
student s;
cout<<"Enter roll number : ";
cin>>rollNumber;
cin.ignore(1000,'\n');
cout<<"Enter name : ";
getline(cin,name);
s.setRollNumber(rollNumber);
s.setName(name.c_str());
fileOutputStream f;
f.open("student.dat",fileOutputStream::append | ios::binary);
f.write((char *)&s,sizeof(student));
f.close();
cout<<"Student added"<<endl;
}
void displayListOfStudents()
{
int rollNumber;
char name[32];
student s;
fileInputStream f;
f.open("student.dat",ios::binary);
if(f.fail())
{
cout<<"No students added"<<endl;
return;
}
while(1)
{
f.read((char *)&s,sizeof(student));
if(f.fail()) break;
rollNumber=s.getRollNumber();
s.getName(name);
cout<<"ROLLNUMBER : "<<rollNumber<<" NAME : "<<name<<endl;
}
f.close();
}
int main()
{
int ch;
while(1)
{
cout<<"1. Add student"<<endl;
cout<<"2. Display list of students"<<endl;
cout<<"3. Exit"<<endl;
cout<<"Enter your choice : ";
cin>>ch;
if(ch==1) addStudent();
else if(ch==2) displayListOfStudents();
else if(ch==3) break;
}
return 0;
}