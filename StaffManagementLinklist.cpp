#include<iostream>
#include<string>
#include<set>
class info{
    public:
    int id;
    std::string name;
    std::string dep;
    info *next;
};
void info_print(info *head);
void find_duplicate(info *head);
void find_id(info *head);
void info_insert(info *head);
void id_modify(info *head);
void HTswap(info **head);
void id_delete(info *head);
int main(){
    info *head=new info;
    head->id=101;
    head->name="Hank";
    head->dep="CST";
    head->next=nullptr;
    info_insert(head);
    info_insert(head);
    HTswap(&head);
    system ("pause");
}
void info_print(info *head){
     if (head == nullptr) {
        std::cout << "Empty List!" << std::endl;
        return;
    }
    while(head!=nullptr){
        std::cout<<head->id;
        if(head->next!=nullptr){
            std::cout<<"->";
        }
        head=head->next;
    }
    std::cout<<std::endl;
    return;
}
void find_duplicate(info *head){
    std::set<int> idrecord;
    if(head==nullptr){
        std::cout<<"No info recorded!"<<std::endl;
        return;
    }
    while (head!=nullptr){
        if(idrecord.find(head->id)==idrecord.cend()){
        idrecord.insert(head->id);
        }
        else{
            std::cout<<"Duplicate Found:"<<std::endl;
            std::cout<<"Staff ID:"<<head->id<<",Name:"<<head->name<<",Department:"<<head->dep<<std::endl;
            break;
        }
        head=head->next;
    }
    return;
}
void find_id(info *head){
    if(head==nullptr){
        std::cout<<"No info recorded!"<<std::endl;
        return;
    }
    int key;
    std::cout<<"Enter Staff ID to search:";
    std::cin>>key;
    while(head!=nullptr)
    {
        if(head->id==key)
        {
            std::cout<<"Staff ID "<<key<<" found at address:"<<head<<std::endl;
            return;
        }
        head=head->next;
    }
    std::cout<<"ID not found!"<<std::endl;
    return;

}
void info_insert(info *head){
    info *headpreserved=head;
    if(head==nullptr){
        std::cout<<"No info recorded!"<<std::endl;
        return;
    }
    info *newnode=new info;
    int index=0;
    std::cout<<"Staff ID:";
    std::cin>>newnode->id;
    std::cout<<"Name:";
    std::cin>>newnode->name;
    std::cout<<"Department:";
    std::cin>>newnode->dep;
    std::cout<<"At index:";
    std::cin>>index;
    for(int i=1;i<index;i++){
        head=head->next;
        if(head==nullptr){
            std::cout<<"Index not found!"<<std::endl;
            delete newnode;
            return;
        }
    }
    //inserting
    newnode->next=head->next;
    head->next=newnode;
    std::cout<<"After inserting at index "<<index<<":"<<std::endl;
    info_print(headpreserved);
}
void id_modify(info *head){
    int pre=0,suf=0;
    std::cout<<"Change Staff ID ";
    std::cin>>pre;
    std::cout<<"->";
    std::cin>>suf;
    std::cout<<"Before modification:";
    info_print(head);
    info *headpreserved=head;
    while(head!=nullptr){
        if(head->id==pre){
            head->id=suf;
            break;
        }
        head=head->next;
    }
    std::cout<<"After modification:";
    info_print(headpreserved);    
}   
void HTswap(info **head){
    std::cout<<"Before swapping:";
    info_print(*head);
    info *oldhead=*head;
    *head=(*head)->next;
    info *tail=*head;
    while(tail->next!=nullptr){
        tail=tail->next;
    }
    tail->next=oldhead;
    oldhead->next=nullptr;
    std::cout<<"After swapping:";
    info_print(*head);
}
void id_delete(info **head){
    std::cout<<"Before Deleting:";
    info_print(*head);
    std::cout<<"Enter the Staff to delete:";
    int key;
    std::cin>>key;
    info *cur=*head;
    info *suf=(*head)->next;
    if((*head)->id==key){
        info *trash=*head;
        *head=(*head)->next;
        delete trash;
        std::cout<<"After Deleting:";
        info_print(*head);
        return;
    }
    while(suf!=nullptr){
        if(suf->id==key){
            cur->next=suf->next;
            delete suf;
            break;
        }
        cur=cur->next;
        suf=suf->next;
    }
    std::cout<<"After Deleting:";
    info_print(*head);
    return;
}