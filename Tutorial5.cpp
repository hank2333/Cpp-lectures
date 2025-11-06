#include <iostream>

void arrayprint(const int *a,int n);
void selection(int *a,int n,int order);
void insertion(int *a,int n,int order);
void bubble(int *a,int n,int order);
int main(){
    std::cout<<"Enter the size of the array:"<<std::endl;
    int n=0;
    std::cin>>n;
    std::cout<<"Enter the array elements:"<<std::endl;
    int *a=new int[n]{0};
    for(int i=0;i<n;i++){
        std::cin>>a[i];
    }
    //now start sorting
    std::cout<<"How do you like to sort? 1.Selection 2.Insertion 3.Bubble"<<std::endl;
    int choice=0;
    std::cin>>choice;
    std::cout<<"Order? 1.Ascending 2.Descending"<<std::endl;
    int order=0;
    std::cin>>order;
    switch(choice){
        case 1:{
            selection(a,n,order);
            break;
        }
        case 2:{
            insertion(a,n,order);
            break;
        }
        case 3:{
            bubble(a,n,order);
            break;
        }
    }
    system("pause");
    return 0;
}

void arrayprint(const int *a,int n){
    for (int i=0;i<n-1;i++){
        std::cout<<a[i]<<",";
    }
    std::cout<<a[n-1]<<std::endl;
}

void selection(int *a,int n,int order){
    if(order==1){
        for(int i=0;i<n;i++){
            int minindex=i;
            for(int j=i+1;j<n;j++){
                if(a[j]<a[minindex]){
                    minindex=j;
                }
            }
            std::swap(a[i],a[minindex]);
            arrayprint(a,n);
        }
    }
    else if(order==2){
        for(int i=0;i<n;i++){
            int maxindex=i;
            for(int j=i+1;j<n;j++){
                if(a[j]>a[maxindex]){
                    maxindex=j;
                }
            }
            std::swap(a[i],a[maxindex]);
            arrayprint(a,n);
        }
    }
    else{
        std::cout<<"Error!"<<std::endl;
    }
}

void insertion(int *a,int n,int order){
    if(order==1){
        for(int i=1;i<n;i++){
            int key=a[i];
            int j=i-1;
            while (j>-1 && a[j]>key)
            {
                a[j+1]=a[j];
                j--;
            }
            a[j+1]=key;
            arrayprint(a,n);
        }
    }
    else if(order==2){
        for(int i=1;i<n;i++){
            int key=a[i];
            int j=i-1;
            while(j>-1 && a[j]<key){
                a[j+1]=a[j];
                j--;
            }
            a[j+1]=key;
            arrayprint(a,n);
        }
    }
}

void bubble(int *a,int n,int order){
    if(order==1){
        for(int i=0;i<n-1;i++){
            for(int j=0;j<n-1-i;j++){
                if(a[j]>a[j+1]){
                    std::swap(a[j],a[j+1]);
                }
            }
            arrayprint(a,n);
        }
    }
    else if(order==2){
        for(int i=0;i<n-1;i++){
            for(int j=0;j<n-1-i;j++){
                if(a[j]<a[j+1]){
                    std::swap(a[j],a[j+1]);
                }
            }
            arrayprint(a,n);
        }
    }
}