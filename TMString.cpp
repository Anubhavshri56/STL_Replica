#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
class TMString
{
private:
char *ptr;
int size;
public:
TMString();
TMString(const char *ptr);
TMString(const TMString &other);
virtual ~TMString();
TMString & operator=(const TMString &other);
TMString & operator=(const char *ptr);
int operator<(const char *ptr);
int operator>(const char *ptr);
int operator<=(const char *ptr);
int operator>=(const char *ptr);
int operator==(const char *ptr);
int operator!=(const char *ptr);
int operator<(const TMString &other);
int operator>(const TMString &other);
int operator<=(const TMString &other);
int operator>=(const TMString &other);
int operator==(const TMString &other);
int operator!=(const TMString &other);
TMString operator+(const char *ptr);
TMString operator+(const TMString &other);
TMString operator*(int);
int find(const TMString &other);
int find(const char *ptr);
int findAndReplace(const TMString &other);
int findAndReplace(const char *ptr);
int findAndReplaceAll(const char *ptr);
int findAndReplaceAll(const TMString &other);
int getSize() const;
void operator+=(const TMString &other);
friend ostream & operator<<(ostream &out,TMString &tmString);
};
TMString::TMString()
{
this->ptr=NULL;
this->size=0;
}
TMString::TMString(const char *ptr)
{
if(ptr==NULL) return;
this->size=strlen(ptr);
this->ptr=new char[this->size+1];
strcpy(this->ptr,ptr);
}
TMString::TMString(const TMString &other)
{
if(other.ptr==NULL) return;
this->size=other.size;
this->ptr=new char[this->size+1];
strcpy(this->ptr,other.ptr);
}
TMString::~TMString()
{
if(this->ptr!=NULL) delete []this->ptr;
}
TMString & TMString::operator=(const TMString &other)
{
if(this->ptr) delete []this->ptr;
this->ptr=NULL;
this->size=0;
if(other.ptr==NULL) return *this;
this->size=other.size;
this->ptr=new char[this->size+1];
strcpy(this->ptr,other.ptr);
return *this;
}
TMString & TMString::operator=(const char *ptr)
{
if(this->ptr) delete []this->ptr;
this->ptr=NULL;
this->size=0;
if(ptr==NULL) return *this;
this->size=strlen(ptr);
this->ptr=new char[this->size+1];
strcpy(this->ptr,ptr);
return *this;
}
int TMString::operator<(const char *ptr)
{
if(ptr==NULL) return 0;
else if(this->ptr==NULL) return 1;
if((strcmp(this->ptr,ptr))<0) return 1;
else return 0;
}
int TMString::operator>(const char *ptr)
{
if(this->ptr==NULL) return 0;
else if(ptr==NULL) return 1;
else if((strcmp(this->ptr,ptr))<=0) return 0;
else return 1;
}
int TMString::operator<=(const char *ptr)
{
if(ptr==NULL && this->ptr==NULL) return 1;
if(ptr==NULL) return 0;
else if(this->ptr==NULL) return 1;
if((strcmp(this->ptr,ptr))<=0) return 1;
else return 0;
}
int TMString::operator>=(const char *ptr)
{
if(ptr==NULL && this->ptr==NULL) return 1;
if(this->ptr==NULL) return 0;
else if(ptr==NULL) return 1;
else if((strcmp(this->ptr,ptr))<0) return 0;
else return 1;
}
int TMString::operator==(const char *ptr)
{
if(ptr==NULL && this->ptr==NULL) return 1;
if(this->ptr==NULL || ptr==NULL) return 0;
if(strcmp(this->ptr,ptr)==0) return 1;
else return 0;
}
int TMString::operator!=(const char *ptr)
{
if(ptr==NULL && this->ptr==NULL) return 0;
if(this->ptr==NULL || ptr==NULL) return 1;
if(strcmp(this->ptr,ptr)==0) return 0;
else return 1;
}
int TMString::operator<(const TMString &other)
{
if(other.ptr==NULL) return 0;
else if(this->ptr==NULL) return 1;
if((strcmp(this->ptr,other.ptr))<0) return 1;
else return 0;
}
int TMString::operator>(const TMString &other)
{
if(this->ptr==NULL) return 0;
else if(other.ptr==NULL) return 1;
if((strcmp(this->ptr,other.ptr))<=0) return 0;
else return 1;
}
int TMString::operator<=(const TMString &other)
{
if(ptr==NULL && this->ptr==NULL) return 1;
if(ptr==NULL) return 0;
else if(this->ptr==NULL) return 1;
if((strcmp(this->ptr,ptr))<=0) return 1;
else return 0;
}
int TMString::operator>=(const TMString &other)
{
if(ptr==NULL && this->ptr==NULL) return 1;
if(this->ptr==NULL) return 0;
else if(ptr==NULL) return 1;
else if((strcmp(this->ptr,ptr))<0) return 0;
else return 1;
}
int TMString::operator==(const TMString &other)
{
if(ptr==NULL && this->ptr==NULL) return 1;
if(this->ptr==NULL || ptr==NULL) return 0;
if(strcmp(this->ptr,ptr)==0) return 1;
else return 0;
}
int TMString::operator!=(const TMString &other)
{
if(ptr==NULL && this->ptr==NULL) return 0;
if(this->ptr==NULL || ptr==NULL) return 1;
if(strcmp(this->ptr,ptr)==0) return 0;
else return 1;
}
TMString TMString::operator+(const char *ptr)
{
TMString local;
local.size=this->size+strlen(ptr);
local.ptr=new char[local.size+1];
strcpy(local.ptr,this->ptr);
if(ptr==NULL) return local;
strcat(local.ptr,ptr);
return local;
}
TMString TMString::operator+(const TMString &other)
{
TMString local;
local.size=this->size+strlen(other.ptr);
local.ptr=new char[local.size+1];
strcpy(local.ptr,this->ptr);
if(other.ptr==NULL) return local;
strcat(local.ptr,other.ptr);
return local;
}
void TMString::operator+=(const TMString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return;
if(other.ptr==NULL) return;
if(this->ptr==NULL)
{
(*this)=other;
return;
}
char *tmp=new char[this->size+other.size+1];
strcpy(tmp,this->ptr);
strcat(tmp,other.ptr);
delete [] this->ptr;
this->ptr=tmp;
this->size=this->size+other.size;
}
TMString TMString::operator*(int times)
{
int e;
TMString local;
for(e=0;e<times;e++)
{
local+=*(this);
}
return local;
}
int TMString::find(const TMString &other)
{
int e,f,foundAt;
if(this->ptr==NULL) return -1;
if(other.ptr==NULL) return -1;
if(this->getSize()<other.getSize()) return -1;
for(e=0;e<this->getSize();)
{
f=0;
if(this->ptr[e]==other.ptr[f])
{
foundAt=e;
for(f=0;f<other.getSize() && e<this->getSize();)
{
if(this->ptr[e]==other.ptr[f])
{
f++;
e++;
}
else break;
}
if(f==other.getSize()) return foundAt;
}
else
{
e++;
}
}
return -1;
}
int TMString::find(const char *ptr)
{
int e,f,foundAt;
if(strlen(this->ptr)<strlen(ptr)) return -1;
if(this->ptr==NULL) return -1;
if(ptr==NULL) return -1;
for(e=0;e<this->getSize();)
{
f=0;
if(this->ptr[e]==ptr[f])
{
foundAt=e;
for(f=0;f<strlen(ptr) && e<this->getSize();)
{
if(this->ptr[e]==ptr[f])
{
f++;
e++;
}
else break;
}
if(f==strlen(ptr)) return foundAt;
}
else
{
e++;
}
}
return -1;
}
int TMString::findAndReplace(const TMString &other)
{
return 0;
}
int TMString::findAndReplace(const char *ptr)
{
return 0;
}
int TMString::findAndReplaceAll(const char *ptr)
{
return 0;
}
int TMString::findAndReplaceAll(const TMString &other)
{
return 0;
}
int TMString::getSize() const
{
return this->size;
}
ostream & operator<<(ostream &out,TMString &tmString)
{
if(tmString.ptr==NULL) return out;
out<<tmString.ptr;
return out;
}
int main()
{
TMString s1="honey bhaiya";
TMString s3="honey yoyo";
cout<<s1.find(s3)<<endl;
return 0;
}