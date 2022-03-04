#include<iostream>
#define bool int
#define false 0
#define true 1
using namespace std;
class TMList
{
public:
virtual void add(int data,bool *success)=0;
virtual void insertAt(int index,int data,bool *success)=0;
virtual int removeAt(int index,bool *success)=0;
virtual void update(int index,int data,bool *success)=0;
virtual int get(int index,bool *success)=0;
virtual void removeAll()=0;
virtual void clear()=0;
virtual int getSize()=0;
};
class TMTwoWayListNode
{
private:
int data;
TMTwoWayListNode *prev;
TMTwoWayListNode *next;
public:
friend class TMTwoWayList;
};
class TMTwoWayList : public TMList
{
private:
TMTwoWayListNode *start,*end;
int size;
public:
TMTwoWayList();
TMTwoWayList(int data);
TMTwoWayList(TMTwoWayList &list);
void add(int data,bool *success);
void insertAt(int index,int data,bool *success);
int removeAt(int index,bool *success);
void update(int index,int data,bool *success);
int get(int index,bool *success);
void removeAll();
void clear();
int getSize();
void display();
void operator=(TMTwoWayList &list);
void operator+=(TMTwoWayList &list);
TMTwoWayList & operator+(TMTwoWayList &list);
int operator[](int index);
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
TMTwoWayList::TMTwoWayList()
{
this->start=NULL;
this->size=0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
TMTwoWayList::TMTwoWayList(int data)
{
TMTwoWayListNode *node;
node=new TMTwoWayListNode;
node->data=data;
node->next=NULL;
node->prev=NULL;
this->start=node;
this->end=node;
this->size=1;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
TMTwoWayList::TMTwoWayList(TMTwoWayList &list)
{
TMTwoWayListNode *iterator,*node;
iterator=list.start;
this->start=NULL;
this->end=NULL;
while(iterator!=NULL)
{
node=new TMTwoWayListNode;
node->data=iterator->data;
node->next=NULL;
if(this->start==NULL)
{
this->start=node;
this->end=node;
}
this->end->next=node;
this->end=node;
iterator=iterator->next;
}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMTwoWayList::add(int data,bool *success)
{
TMTwoWayListNode *node,*iterator;
if(success) *success=false;
node=new TMTwoWayListNode;
if(node==NULL) return;
node->data=data;
node->next=NULL;
node->prev=NULL;
if(this->start==NULL)
{
this->start=node;
this->end=node;
}
else
{
iterator=this->start;
while(iterator->next!=NULL) iterator=iterator->next;
iterator->next=node;
node->prev=iterator;
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
if(index<0 || index>=getSize())
{
return *success;
}
for(current=this->start,iterator=0;current->next!=NULL && iterator<index;current=current->next,iterator++);
if(current==this->start)
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
if(success) *success=true;
return data;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMTwoWayList::update(int index,int data,bool *success)
{
TMTwoWayListNode *node,*current;
int iteratorIndex;
if(success) *success=false;
if(index<0 || index>=getSize())
{
return;
}
for(current=this->start,iteratorIndex=0;current->next!=NULL && iteratorIndex<index;current=current->next,iteratorIndex++);
current->data=data;
if(success) *success=true;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMTwoWayList::get(int index,bool *success)
{
TMTwoWayListNode *node,*current;
int iteratorIndex;
if(success) *success=false;
if(index<0 || index>=getSize())
{
return *success;
}
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
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMTwoWayList::getSize()
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
void TMTwoWayList::operator=(TMTwoWayList &list)
{
TMTwoWayListNode *iterator,*node;
iterator=list.start;
while(iterator!=NULL)
{
node=new TMTwoWayListNode;
node->data=iterator->data;
node->next=NULL;
if(this->start==NULL)
{
this->start=node;
this->end=node;
}
this->end->next=node;
this->end=node;
iterator=iterator->next;
}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
void TMTwoWayList::operator+=(TMTwoWayList &list)
{
TMTwoWayListNode *iterator,*node;
iterator=list.start;
while(iterator!=NULL)
{
node=new TMTwoWayListNode;
node->data=iterator->data;
node->next=NULL;
if(this->start==NULL)
{
this->start=node;
this->end=node;
}
this->end->next=node;
this->end=node;
iterator=iterator->next;
}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
TMTwoWayList & TMTwoWayList::operator+(TMTwoWayList &list)
{
TMTwoWayListNode *iterator,*node;
iterator=list.start;
while(iterator!=NULL)
{
node=new TMTwoWayListNode;
node->data=iterator->data;
node->next=NULL;
if(this->start==NULL)
{
this->start=node;
this->end=node;
}
this->end->next=node;
this->end=node;
iterator=iterator->next;
}
return *this;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
int TMTwoWayList::operator[](int index)
{
if(index>getSize()) return 0;
int iterator=0;
TMTwoWayListNode *list;
for(list=this->start;iterator<index;list=list->next,iterator++);
return list->data;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
bool success;
TMTwoWayList list;
list.add(23,&success);
if(success)
{
cout<<"Number Added\n";
}
else
{
cout<<"Cannot Add Number\n";
}
list.add(42,&success);
if(success)
{
cout<<"Number Added\n";
}
else
{
cout<<"Cannot Add Number\n";
}
list.add(20,&success);
list.add(40,&success);
list.add(60,&success);
TMTwoWayList list2(list),list3;
cout<<list[1]<<endl<<list[0]<<endl;
cout<<"List 1\n";
list.display();
cout<<"List 2\n";
list2.display();
list2+=list;
cout<<"List 2\n";
list2.display();
list3=list+list2;
cout<<"List 3\n";
list3.display();
return 0;
}