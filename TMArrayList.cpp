#include<iostream>
#define bool int
#define false 0
#define true 1
using namespace std;
class TMList
{
public:
virtual void add(int data,bool *success)=0;
virtual int get(int index,bool *success) const=0;
virtual void insertAt(int index,int data,bool *success)=0;
virtual int removeAt(int index,bool *success)=0;
virtual void update(int index,int data,bool *success)=0;
virtual void removeAll()=0;
virtual void clear()=0;
virtual int getSize()=0;
};
class TMArrayList : public TMList
{
private:
int **ptr;
int size,capacity;
char flag;
public:
TMArrayList();
TMArrayList(int data);
TMArrayList(const TMArrayList &list);
virtual ~TMArrayList();
bool addRow();
void add(int data,bool *success);
int get(int index,bool *success) const;
void insertAt(int index,int data,bool *success);
int removeAt(int index,bool *success);
void update(int index,int data,bool *success);
void removeAll();
void clear();
int getSize();
void display();
TMArrayList & operator=(const TMArrayList &other);
void operator+=(TMArrayList &other);
TMArrayList operator+(TMArrayList &other);
int operator[](int index);
};
TMArrayList::TMArrayList()
{
this->ptr=new int *[10];
this->ptr[0]=new int [10];
this->capacity=10;
this->flag='0';
this->size=0;
}
TMArrayList::TMArrayList(int bufferSize)
{
int rows,numberOfPointer;
if(bufferSize<=0)
{
this->ptr=new int *[10];
this->ptr[0]=new int [10];
this->capacity=10;
this->size=0;
this->flag='0';
}
else
{
rows=bufferSize/10;
if(bufferSize%10!=0) rows++;
numberOfPointer=rows+(10-(rows%10));
this->ptr=new int *[numberOfPointer];
for(int e=0;e<rows;e++) this->ptr[e]=new int [10];
this->capacity=rows*10;
this->size=0;
this->flag='0';
}
}
TMArrayList::TMArrayList(const TMArrayList &other)
{
int bufferSize=other.size,succ;
int rows,numberOfPointer;
if(bufferSize<=0)
{
this->ptr=new int *[10];
this->ptr[0]=new int [10];
this->capacity=10;
this->size=0;
this->flag='0';
}
else
{
rows=bufferSize/10;
if(bufferSize%10!=0) rows++;
numberOfPointer=rows+(10-(rows%10));
this->ptr=new int *[numberOfPointer];
for(int e=0;e<rows;e++) this->ptr[e]=new int [10];
this->capacity=rows*10;
this->size=0;
this->flag='0';
}
for(int e=0;e<other.size;e++)
{
this->add(other.get(e,&succ),&succ);
}
}
TMArrayList::~TMArrayList()
{
if(this->flag=='0')
{
this->ptr=NULL;
return;
}
int row;
row=this->size/10;
for(int i=0;i<=row;i++) delete[] this->ptr[i];
delete[] this->ptr;
}
TMArrayList & TMArrayList::operator=(const TMArrayList &other)
{
if(other.flag=='1')
{
int row=this->size/10;
for(int i=0;i<=row;i++) delete []this->ptr[i];
delete []this->ptr;
this->ptr=other.ptr;
this->size=other.size;
this->capacity=other.capacity;
return *this;
}
this->size=0;
int succ;
for(int e=0;e<other.size;e++) this->add(other.get(e,&succ),&succ);
return *this;
}
void TMArrayList::operator+=(TMArrayList &other)
{
int succ;
for(int e=0;e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
}
TMArrayList TMArrayList::operator+(TMArrayList &other)
{
TMArrayList local;
int succ,e;
local.flag='1';
for(e=0;e<this->size;e++) local.add(this->get(e,&succ),&succ);
for(e=0;e<other.size;e++) local.add(other.get(e,&succ),&succ);
return local;
}
bool TMArrayList::addRow()
{
if(capacity%100==0)
{
int numberOfPointers;
numberOfPointers=this->capacity/10;
int **temp=new int *[numberOfPointers+10];
if(temp==NULL) return false;
for(int e=0;e<numberOfPointers;e++) temp[e]=this->ptr[e];
delete [] this->ptr;
this->ptr=temp;
}
int i=this->capacity/10;
this->ptr[i]=new int[10];
this->capacity+=10;
return true;
}
void TMArrayList::add(int data,bool *success)
{
int rowIndex,columnIndex;
if(success) *success=false;
if(this->size==this->capacity) if(!addRow()) return;
rowIndex=size/10;
columnIndex=size%10;
this->ptr[rowIndex][columnIndex]=data;
this->size++;
if(success) *success=true;
}
int TMArrayList::get(int index,bool *success) const
{
if(success) *success=false;
if(index<0 || index>this->size) return 0;
int rowIndex,columnIndex;
rowIndex=index/10;
columnIndex=index%10;
return this->ptr[rowIndex][columnIndex];
}
void TMArrayList::insertAt(int index,int data,bool *success)
{
if(success) *success=false;
if(index<0 || index>this->size) return;
bool succ;
if(index==this->size)
{
this->add(data,success);
return;
}
this->add(this->get(size-1,&succ),&succ);
if(succ==false) return;
int j=this->size-3;
while(j>=index)
{
this->update(j+1,this->get(j,&succ),&succ);
j--;
}
this->update(index,data,&succ);
if(success) *success=true;
}
int TMArrayList::removeAt(int index,bool *success)
{
if(success) *success=false;
if(index<0 || index>=this->size) return 0;
bool succ;
int data=this->get(index,&succ);
int j=index;
while(j<this->size-1)
{
this->update(j,this->get(j+1,&succ),&succ);
j++;
}
this->size--; 
if(success) *success=true;
return data;
}
void TMArrayList::update(int index,int data,bool *success)
{
if(success) *success=false;
if(index<0 || index>=this->size) return;
int rowIndex,columnIndex;
rowIndex=index/10;
columnIndex=index%10;
this->ptr[rowIndex][columnIndex]=data;
if(success) *success=true;
}
void TMArrayList::removeAll()
{
this->size=0;
}
void TMArrayList::clear()
{this->size=0;
}
int TMArrayList::getSize()
{
return this->size;
}
int main()
{
TMArrayList list1;
bool succ;
for(int e=0;e<15;e++) list1.add(e,&succ);
cout<<"LIST 1\n";
for(int e=0;e<list1.getSize();e++) cout<<list1.get(e,&succ)<<" ";
cout<<endl;
TMArrayList list2;
for(int e=530;e<570;e++) list2.add(e,&succ);
cout<<"LIST 2\n";
for(int e=0;e<list2.getSize();e++) cout<<list2.get(e,&succ)<<" ";
TMArrayList list3;
list3=list1+list2;
cout<<"\nList 3\n";
cout<<list3.getSize()<<endl;
for(int e=0;e<list3.getSize();e++)
{
cout<<list3.get(e,&succ)<<" ";
}

return 0;
}