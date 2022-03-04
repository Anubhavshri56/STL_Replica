#include<iostream>
#define bool int
#define false 0
#define true 1
using namespace std;
class Iterator
{
private:
char releaseIteratorAfterIteration;
Iterator *iterator;
public:
Iterator()
{
this->releaseIteratorAfterIteration='1';
this->iterator=NULL;
}
Iterator(Iterator *iterator)
{
this->releaseIteratorAfterIteration='1';
this->iterator=iterator;
}
Iterator(const Iterator& other)
{
this->releaseIteratorAfterIteration='1';
this->iterator=other.iterator;
}
Iterator & operator=(const Iterator &other)
{
this->iterator=other.iterator;
return *this;
}
virtual ~Iterator()
{
if(this->releaseIteratorAfterIteration=='1') delete this->iterator;
}
void setRealeaseIteratorAfterIteration(char releaseIteratorAfterIteration)
{
this->releaseIteratorAfterIteration=releaseIteratorAfterIteration;
}
virtual int hasMoreElement()
{
if(this->iterator!=NULL) return this->iterator->hasMoreElement();
else return 0;
}
virtual int next()
{
if(this->iterator!=NULL) return this->iterator->next();
else return 0;
}
};
class Iterable
{
public:
virtual Iterator getIterator()=0;
};
class TMList:public Iterable
{
public:
virtual void add(int data,bool *success)=0;
virtual void insertAt(int index,int data,bool *success)=0;
virtual int removeAt(int index,bool *success)=0;
virtual void update(int index,int data,bool *success)=0;
virtual int get(int index,bool *success) const=0;
virtual void removeAll()=0;
virtual void clear()=0;
virtual int getSize() const=0;
};
class TMArrayList : public TMList
{
private:
int **ptr;
int size,capacity;
char flag;
public:
class TMArrayListIterator : public Iterator
{
private:
int index;
int size;
int **ptr;
public:
TMArrayListIterator(int **ptr,int size)
{
this->index=0;
this->size=size;
this->ptr=ptr;
}
TMArrayListIterator(const TMArrayListIterator &other)
{
this->index=other.index;
}
TMArrayListIterator & operator=(const TMArrayListIterator & other)
{
this->index=other.index;
return *this;
}
int hasMoreElement()
{
return this->ptr!=NULL;
}
int next()
{
if(this->index==size) return 0;
int rowIndex=index/10;
int columnIndex=index%10;
int data=this->ptr[rowIndex][columnIndex];
index++;
return data;
}
};
Iterator getIterator()
{
TMArrayListIterator *tmArrayListIterator;
tmArrayListIterator=new TMArrayListIterator(this->ptr,this->size);
Iterator k(tmArrayListIterator);
k.setRealeaseIteratorAfterIteration('0');
return k;
}
TMArrayList();
TMArrayList(int data);
TMArrayList(const TMArrayList &other);
TMArrayList(const TMList &other);
virtual ~TMArrayList();
bool addRow();
void add(int data,bool *success);
int get(int index,bool *success) const;
void insertAt(int index,int data,bool *success);
int removeAt(int index,bool *success);
void update(int index,int data,bool *success);
void removeAll();
void clear();
int getSize() const;
void display();
TMArrayList & operator=(const TMArrayList &other);
void operator+=(TMArrayList &other);
TMArrayList operator+(TMArrayList &other);
TMArrayList & operator=(const TMList &other);
void operator+=(TMList &other);
TMArrayList operator+(TMList &other);
int operator[](int index);
bool flagValue();
};
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
TMArrayList::TMArrayList()
{
this->ptr=new int *[10];
this->ptr[0]=new int [10];
this->capacity=10;
this->flag='0';
this->size=0;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
TMArrayList::TMArrayList(const TMList &other)
{
int succ,bufferSize=other.getSize();
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
for(int e=0;e<other.getSize();e++)
{
this->add(other.get(e,&succ),&succ);
}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
TMArrayList & TMArrayList::operator=(const TMList &other)
{
if(flagValue())
{
int row=this->getSize()/10;
for(int i=0;i<=row;i++) delete []this->ptr[i];
delete []this->ptr;
}
this->size=0;
int succ;
for(int e=0;e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMArrayList::operator+=(TMArrayList &other)
{
int succ;
for(int e=0;e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
}
void TMArrayList::operator+=(TMList &other)
{
int succ;
for(int e=0;e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
}
TMArrayList TMArrayList::operator+(TMArrayList &other)
{
TMArrayList local;
int succ,e;
local.flag='1';
for(e=0;e<this->size;e++) local.add(this->get(e,&succ),&succ); //local+=(*this);
for(e=0;e<other.size;e++) local.add(other.get(e,&succ),&succ);//local+=other;
return local;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
TMArrayList TMArrayList::operator+(TMList &other)
{
TMArrayList local;
int succ,e;
local.flag='1';
for(e=0;e<this->getSize();e++) local.add(this->get(e,&succ),&succ);
for(e=0;e<other.getSize();e++) local.add(other.get(e,&succ),&succ);
return local;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMArrayList::operator[](int index)
{
int succ;
if(index<0 || index>=this->getSize()) return -1;
else return get(index,&succ);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
bool TMArrayList::flagValue()
{
return this->flag;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMArrayList::get(int index,bool *success) const
{
if(success) *success=false;
if(index<0 || index>this->size) return 0;
int rowIndex,columnIndex;
rowIndex=index/10;
columnIndex=index%10;
return this->ptr[rowIndex][columnIndex];
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMArrayList::removeAll()
{
this->size=0;
}
void TMArrayList::clear()
{
this->size=0;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMArrayList::getSize() const
{
return this->size;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
class TMForwardList : public TMList
{
private:
class TMForwardListNode
{
public:
int data;
TMForwardListNode *next;
TMForwardListNode()
{
this->next=NULL;
}
};
TMForwardListNode *start,*end;
int size;
char flag;
public:
class TMForwardListIterator : public Iterator
{
private:
TMForwardListNode *ptr;
public:
TMForwardListIterator()
{
this->ptr=NULL;
}
TMForwardListIterator(TMForwardListNode *ptr)
{
this->ptr=ptr;
}
TMForwardListIterator(const TMForwardListIterator &other)
{
this->ptr=other.ptr;
}
TMForwardListIterator & operator=(const TMForwardListIterator & other)
{
this->ptr=other.ptr;
return *this;
}
int hasMoreElement()
{
return this->ptr!=NULL;
}
int next()
{
if(this->ptr==NULL) return 0;
int data=this->ptr->data;
this->ptr=this->ptr->next;
return data;
}
};
Iterator getIterator()
{
TMForwardListIterator *tmForwardListIterator;
tmForwardListIterator=new TMForwardListIterator(this->start);
Iterator k(tmForwardListIterator);
k.setRealeaseIteratorAfterIteration('0');
return k;
}
TMForwardList();
TMForwardList(int data);
TMForwardList(const TMForwardList &list);
TMForwardList(const TMList &list);
virtual ~TMForwardList();
void add(int data,bool *success);
void insertAt(int index,int data,bool *success);
int removeAt(int index,bool *success);
void update(int index,int data,bool *success);
int get(int index,bool *success) const;
void removeAll();
void clear();
int getSize() const;
void display();
TMForwardList & operator=(const TMForwardList &list);
void operator+=(TMForwardList &list);
TMForwardList operator+(TMForwardList &list);
TMForwardList & operator=(const TMList &list);
void operator+=(TMList &list);
TMForwardList operator+(TMList &list);
int operator[](int index);
};
TMForwardList::TMForwardList()
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->flag=0;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
TMForwardList::TMForwardList(int bufferSize)
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->flag=0;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
TMForwardList::TMForwardList(const TMForwardList &other)
{
int succ;
this->start=NULL;
this->end=NULL;
this->size=0;
this->flag='0';
for(int e=0;e<other.size;e++) this->add(other.get(e,&succ),&succ);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
TMForwardList::TMForwardList(const TMList &other)
{
int succ;
this->start=NULL;
this->end=NULL;
this->size=0;
this->flag='0';
for(int e=0;e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
TMForwardList::~TMForwardList()
{
if(this->flag==0)
{
this->clear();
}
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
TMForwardList & TMForwardList::operator=(const TMForwardList &other)
{
if(other.flag==1)
{
this->removeAll();
this->start=other.start;
this->end=other.end;
this->size=other.size;
}
else
{
int succ;
this->removeAll();
for(int i=0;i<other.getSize();i++) this->add(other.get(i,&succ),&succ);
}
return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
TMForwardList & TMForwardList::operator=(const TMList &other)
{
int succ;
this->removeAll();
for(int i=0;i<other.getSize();i++) this->add(other.get(i,&succ),&succ);
return *this;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMForwardList::operator+=(TMForwardList &other)
{
int succ;
for(int e=0;e<other.size;e++) this->add(other.get(e,&succ),&succ);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMForwardList::operator+=(TMList &other)
{
int succ;
for(int e=0;e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
TMForwardList TMForwardList::operator+(TMForwardList &other)
{
TMForwardList local;
int succ;
for(int i=0;i<this->size;i++) local.add(this->get(i,&succ),&succ);
for(int i=0;i<other.size;i++) local.add(other.get(i,&succ),&succ);
local.flag='1';
return local;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
TMForwardList TMForwardList::operator+(TMList &other)
{
TMForwardList local;
int succ;
for(int i=0;i<this->getSize();i++) local.add(this->get(i,&succ),&succ);
for(int i=0;i<other.getSize();i++) local.add(other.get(i,&succ),&succ);
local.flag='1';
return local;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMForwardList::operator[](int index)
{
int succ;
if(index<0 || index>=this->getSize()) return -1;
else return get(index,&succ);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMForwardList::add(int data,bool *success)
{
TMForwardListNode *node;
if(success) *success=false;
node=new TMForwardListNode;
if(node==NULL) return;
node->data=data;
node->next=NULL;
if(this->start==NULL)
{
this->start=node;
this->end=node;
}
else
{
this->end->next=node;
this->end=node;
}
this->size++;
if(success) *success=true;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMForwardList::insertAt(int index,int data,bool *success)
{
TMForwardListNode *node,*iterator,*current,*previous;
int iteratorIndex;
if(success) *success=false;
if(index<0 || index>getSize()) return;
for(current=this->start,iteratorIndex=0;iteratorIndex<index;previous=current,current=current->next,iteratorIndex++);
node=new TMForwardListNode;
node->data=data;
node->next=NULL;
if(current==this->start)
{
node->next=this->start;
this->start=node;
}
else if(current==NULL)
{
previous->next=node;
this->end=node;
}
else
{
previous->next=node;
node->next=current;
}
this->size++;
if(success) *success=true;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMForwardList::removeAt(int index,bool *success)
{
TMForwardListNode *node,*current,*previous;
int iterator,data;
if(success) *success=false;
if(index<0 || index>=getSize())
{
return *success;
}
for(current=this->start,iterator=0;iterator<index;previous=current,current=current->next,iterator++);
if(current==this->start && current==this->end) this->start=this->end=NULL;
else if(current==this->start) this->start=this->start->next;
else if(current->next==NULL)
{
previous->next=NULL;
this->end=previous;
}
else previous->next=current->next;
data=current->data;
delete current;
this->size--;
if(success) *success=true;
return data;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMForwardList::update(int index,int data,bool *success)
{
TMForwardListNode *current;
int iteratorIndex;
if(success) *success=false;
if(index<0 || index>=getSize()) return;
for(current=this->start,iteratorIndex=0;iteratorIndex<index;current=current->next,iteratorIndex++);
current->data=data;
if(success) *success=true;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMForwardList::get(int index,bool *success) const
{
TMForwardListNode *node,*current;
int iteratorIndex;
if(success) *success=false;
if(index<0 || index>=this->size)
{
return *success;
}
for(current=this->start,iteratorIndex=0;iteratorIndex<index;current=current->next,iteratorIndex++);
if(success) *success=true;
return current->data;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMForwardList::removeAll()
{
TMForwardListNode *node,*current,*previous;
for(current=this->start;current!=NULL;)
{
previous=current;
current=current->next;
delete previous;
}
this->start=NULL;
this->end=NULL;
this->size=0;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMForwardList::clear()
{
TMForwardListNode *node,*current,*previous;
for(current=this->start;current!=NULL;)
{
previous=current;
current=current->next;
delete previous;
}
this->start=NULL;
this->end=NULL;
this->size=0;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMForwardList::getSize() const
{
return this->size;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMForwardList::display()
{
TMForwardListNode *node;
for(node=this->start;node!=NULL;node=node->next) cout<<node->data<<endl;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
class TMTwoWayList : public TMList
{
private:
class TMTwoWayListNode
{
public:
int data;
TMTwoWayListNode *prev;
TMTwoWayListNode *next;
};
TMTwoWayListNode *start,*end;
int size;
char flag;
public:
class TMTwoWayListIterator : public Iterator
{
private:
TMTwoWayListNode *ptr;
public:
TMTwoWayListIterator()
{
this->ptr=NULL;
}
TMTwoWayListIterator(TMTwoWayListNode *ptr)
{
this->ptr=ptr;
}
TMTwoWayListIterator(const TMTwoWayListIterator &other)
{
this->ptr=other.ptr;
}
TMTwoWayListIterator & operator=(const TMTwoWayListIterator & other)
{
this->ptr=other.ptr;
return *this;
}
int hasMoreElement()
{
return this->ptr!=NULL;
}
int next()
{
if(this->ptr==NULL) return 0;
int data=this->ptr->data;
this->ptr=this->ptr->next;
return data;
}
};
Iterator getIterator()
{
TMTwoWayListIterator *tmTwoWayListIterator;
tmTwoWayListIterator=new TMTwoWayListIterator(this->start);
Iterator k(tmTwoWayListIterator);
k.setRealeaseIteratorAfterIteration('0');
return k;
}
TMTwoWayList();
TMTwoWayList(int data);
TMTwoWayList(const TMTwoWayList &list);
TMTwoWayList(const TMList &list);
virtual ~TMTwoWayList();
void add(int data,bool *success);
void insertAt(int index,int data,bool *success);
int removeAt(int index,bool *success);
void update(int index,int data,bool *success);
int get(int index,bool *success) const;
void removeAll();
void clear();
int getSize() const;
void display();
TMTwoWayList & operator=(const TMTwoWayList &list);
void operator+=(TMTwoWayList &list);
TMTwoWayList operator+(TMTwoWayList &list);
TMTwoWayList & operator=(const TMList &list);
void operator+=(TMList &list);
TMTwoWayList operator+(TMList &list);
int operator[](int index);
};
//did did
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
TMTwoWayList::TMTwoWayList()
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->flag='0';
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
TMTwoWayList::TMTwoWayList(int bufferSize)
{
this->start=NULL;
this->end=NULL;
this->size=0;
this->flag='0';
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
TMTwoWayList::TMTwoWayList(const TMTwoWayList &other)
{
int e,succ;
this->start=NULL;
this->end=NULL;
this->size=0;
this->flag='0';
for(e=0;e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
TMTwoWayList::TMTwoWayList(const TMList &other)
{
int e,succ;
this->start=NULL;
this->end=NULL;
this->size=0;
this->flag='0';
for(e=0;e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
TMTwoWayList::~TMTwoWayList()
{
if(this->flag==0)
{
this->clear();
}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
TMTwoWayList & TMTwoWayList::operator=(const TMTwoWayList &other)
{
int succ;
if(other.flag=='1')
{
this->clear();
this->start=other.start;
this->end=other.end;
this->size=other.size;
}
if(this->start!=NULL) this->clear();
for(int e=0;e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
return *this;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMTwoWayList::operator+=(TMTwoWayList &other)
{
int e,succ;
for(e=0;e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
TMTwoWayList TMTwoWayList::operator+(TMTwoWayList &other)
{
int e,succ;
TMTwoWayList local;
for(e=0;e<this->getSize();e++) local.add(this->get(e,&succ),&succ);
for(e=0;e<other.getSize();e++) local.add(other.get(e,&succ),&succ);
local.flag='1';
return local;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
TMTwoWayList & TMTwoWayList::operator=(const TMList &other)
{
int succ;
this->clear();
for(int e=0;e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
return *this;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMTwoWayList::operator+=(TMList &other)
{
int e,succ;
for(e=0;e<other.getSize();e++) this->add(other.get(e,&succ),&succ);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
TMTwoWayList TMTwoWayList::operator+(TMList &other)
{
int e,succ;
TMTwoWayList local;
for(e=0;e<this->getSize();e++) local.add(this->get(e,&succ),&succ);
for(e=0;e<other.getSize();e++) local.add(other.get(e,&succ),&succ);
local.flag='1';
return local;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMTwoWayList::operator[](int index)
{
int succ;
if(index<0 || index>=this->getSize()) return -1;
else return get(index,&succ);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMTwoWayList::add(int data,bool *success)
{
TMTwoWayListNode *node;
if(success) *success=false;
node=new TMTwoWayListNode;
node->data=data;
node->next=NULL;
node->prev=NULL;
if(this->start==NULL && this->end==NULL)
{
this->start=node;
this->end=node;
}
else
{
this->end->next=node;
this->end=node;
}
this->size++;
if(success) *success=true;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMTwoWayList::insertAt(int index,int data,bool *success)
{
TMTwoWayListNode *node,*iterator,*current;
int iteratorIndex;
if(success) *success=false;
if(index<0 || index>getSize()) return;
for(current=this->start,iteratorIndex=0;current!=NULL && iteratorIndex<index;current=current->next,iteratorIndex++);
node=new TMTwoWayListNode;
node->data=data;
node->next=NULL;
node->prev=NULL;
if(current==this->start)
{
node->next=this->start;
this->start=node;
}
else if(current==NULL)
{
this->end->next=node;
node->prev=this->end;
this->end=node;
}
else
{
node->next=current;
current->prev->next=node;
node->prev=current->prev;
current->prev=node;
}
this->size++;
if(success) *success=true;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMTwoWayList::removeAt(int index,bool *success)
{
TMTwoWayListNode *node,*current;
int iterator,data;
if(success) *success=false;
if(index<0 || index>=getSize()) return *success;
for(current=this->start,iterator=0;current->next!=NULL && iterator<index;current=current->next,iterator++);
if(current==this->start && current==this->end) this->start=this->end=NULL;
else if(current==this->start)
{
start=start->next;
start->prev=NULL;
}
else if(current->next==NULL)
{
current->prev->next=NULL;
this->end=current->prev;
}
else
{
current->prev->next=current->next;
current->next->prev=current->prev;
}
data=current->data;
delete current;
this->size--;
if(success) *success=true;
return data;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMTwoWayList::update(int index,int data,bool *success)
{
TMTwoWayListNode *node,*current;
int iteratorIndex;
if(success) *success=false;
if(index<0 || index>=getSize()) return;
for(current=this->start,iteratorIndex=0;current->next!=NULL && iteratorIndex<index;current=current->next,iteratorIndex++);
current->data=data;
if(success) *success=true;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMTwoWayList::get(int index,bool *success) const
{
TMTwoWayListNode *node,*current;
int iteratorIndex;
if(success) *success=false;
if(index<0 || index>=getSize()) return *success;
for(current=this->start,iteratorIndex=0;current->next!=NULL && iteratorIndex<index;current=current->next,iteratorIndex++);
if(success) *success=true;
return current->data;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMTwoWayList::removeAll()
{
TMTwoWayListNode *node,*current,*previous;
for(current=this->start;current!=NULL;)
{
previous=current;
current=current->next;
delete previous;
}
this->start=NULL;
this->end=NULL;
this->size=0;
this->flag='0';
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMTwoWayList::clear()
{
TMTwoWayListNode *node,*current,*previous;
for(current=this->start;current!=NULL;)
{
previous=current;
current=current->next;
delete previous;
}
this->start=NULL;
this->end=NULL;
this->size=0;
this->flag='0';
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMTwoWayList::getSize() const
{
return this->size;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMTwoWayList::display()
{
TMTwoWayListNode *node;
for(node=this->start;node!=NULL;node=node->next) cout<<node->data<<endl;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
bool success;
int num;
TMTwoWayList list1;
list1.add(102,&success);
list1.add(123,&success);
list1.add(234,&success);
list1.add(98,&success);
list1.add(-123,&success);
list1.add(-8,&success);
list1.add(56,&success);
list1.add(9,&success);
list1.add(101,&success);
for(int e=0;e<9;e++) cout<<list1[e]<<endl;
return 0;
}