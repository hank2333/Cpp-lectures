//implement of link list using cpp

#include <iostream>
using namespace std;
class Node{
    public:
    int data;
    Node *next;
    Node (int n):data(n),next(nullptr){};
};
void printlist(Node* head);
int findvalue(Node* head,int num);
void insert_back(Node* head,int n);
void insert_front(Node* &head,int n);
void insert_after(Node* head,int n,int pos);
void delete_pos(Node* &head,int pos);
void delete_value(Node* &head,int key);
int main(){
    Node *head =new Node(1);
    Node *node2=new Node(2);
    Node *node3=new Node(3);

    head->next=node2;
    node2->next=node3;
    node3->next=nullptr;
    insert_back(head,4);
    insert_after(head,10,1);
    delete_value(head,4);
    printlist(head);
    system("pause");
    return 0;
}

void printlist(Node *head){
    if(head==nullptr){
        cout<<"The list is empty!"<<endl;
        return;
    }
    cout<<"The elements in the link list are:";
    while (head!=nullptr)
    {
        cout<<head->data<<" ";
        head=head->next;
    }
    cout<<endl;
}

int  findvalue(Node *head,int num){
    if(head==nullptr)
    {
        cout<<"The list is empty!"<<endl;
        return -1;
    }
    int pos=1;
    while(head!=nullptr){
        if (head->data == num) {
            return pos;
        }
        head = head->next;
        pos++;
    }
    return -1;
}
void insert_back(Node *head,int n){
    while(head->next!=nullptr){
        head=head->next;
    }
    Node *newnode=new Node(n);
    head->next=newnode;
}
void insert_front(Node* &head,int n){
    Node *newnode=new Node(n);
    newnode->next=head;
    head=newnode;
}
void insert_after(Node* head,int n,int pos){
    if(head==nullptr){
        cout<<"The list is empty!"<<endl;
        return;
    }
    for(int i=1;i<pos;i++){
        head=head->next;
        if(head==nullptr){
            cout<<"Position can't reach!"<<endl;
            return;
        }
    }
    Node* newnode=new Node(n);
    newnode->next=head->next;
    head->next=newnode;
}
void delete_pos(Node* &head,int pos){
    if(head==nullptr || pos < 1){
        cout<<"Invalid position!"<<endl;
        return;
    }
    if(pos==1){
        Node* rubbish=head;
        head=head->next;
        delete rubbish;
        return;
    }
    Node* curr=head;
    for(int i=1;i<pos-1;i++){
        if(curr==nullptr || curr->next==nullptr){
            cout<<"Position can't reach!"<<endl;
            return;
        }
        curr=curr->next;
    }
    Node* rubbish=curr->next;
    if(rubbish==nullptr){
        cout<<"Position can't reach!"<<endl;
        return;
    }
    curr->next=rubbish->next;
    delete rubbish;
}
void delete_value(Node* &head,int key){
    int pos = findvalue(head,key);
    if(pos == -1){
        cout<<"Value not found!"<<endl;
        return;
    }
    delete_pos(head,pos);
}
