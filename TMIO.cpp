#include<iostream>
#include<string.h>
#include<stdio.h>
#include<fstream>
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
};

void addInfo()
{
int e;
char name[32],contactNumber[82];
cout<<"Enter name : ";
fgets(name,32,stdin);
fflush(stdin);
name[strlen(name)-1]='\0';
for(e=0;name[e]!='\0';e++)
{
if(name[e]=='!')
{
cout<<"Name cannot contain '!'"<<endl;
return;
}
}
cout<<"Enter Contact Number : ";
fgets(contactNumber,82,stdin);
contactNumber[strlen(contactNumber)-1]='\0';
fflush(stdin);
for(e=0;contactNumber[e]!='\0';e++)
{
if(contactNumber[e]=='!')
{
cout<<"contact number cannot contain '!'"<<endl;
return;
}
}
fileOutputStream f;
f.open("file.fil",fileOutputStream::append);
for(e=0;name[e]!='\0';e++)
{
f<<name[e];
}
f<<'!';
for(e=0;contactNumber[e]!='\0';e++)
{
f<<contactNumber[e];
}
f<<'!';
f.close();
}

void displayList()
{
int e;
char name[32],cn[82],c;
fileInputStream f;
f.open("file.fil");
if(f.fail())
{
cout<<"nothing in the file"<<endl;
return;
}
while(1)
{
f>>c;
if(f.fail()) break;
name[0]=c;
for(e=1;1;e++)
{
f>>c;
if(c=='!') break;
name[e]=c;
}
name[e]='\0';
for(e=0;1;e++)
{
f>>c;
if(c=='!') break;
cn[e]=c;
}
cn[e]='\0';
printf("NAME : %s CONTACT NUMBER : %s\n",name,cn);
}
f.close();
}

int main()
{
int ch;
while(1)
{
cout<<"1. Add info\n";
cout<<"2. display List"<<endl;
cout<<"3. Exit"<<endl;
cout<<"Enter your choice : ";
scanf("%d",&ch);
fflush(stdin);
if(ch==1) addInfo();
else if(ch==2) displayList();
else if(ch==3) break;
}
return 0;
}