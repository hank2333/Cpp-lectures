#include <iostream>
#include <cstring>//include functions like strlen/strcpy

class MiniString{
    public:
    MiniString():data(nullptr),len(0),capacity(0){};
    MiniString(const char* s);
    MiniString(const MiniString& other);
    MiniString(MiniString&& other) noexcept;
    MiniString& operator= (const MiniString& other);
    MiniString& operator= (MiniString&& other) noexcept;
    ~MiniString();
    std::size_t size() const;
    const char* c_str() const;
    void push_back(char c);

    private:
    char *data = nullptr;
    size_t len = 0;//valid char number
    size_t capacity = 0;//storage char number including \0
};

MiniString::MiniString(const char* s){
    if(!s){
        data=nullptr;
        len=0;
        capacity=0;
        return;
    }//need to check if the pointer is nullptr in following context
    len = std::strlen(s);//if s is nullptr,this function will colapse
    capacity = len + 1;
    data = new char[capacity];
    std::memcpy(data,s,capacity);
}

MiniString::MiniString(const MiniString& other){
    len = other.len;
    capacity = other.capacity;//better to copy other member first to make error alignment
    data = new char[capacity];
    std::memcpy(data,other.data,capacity);
}

MiniString::MiniString(MiniString&& other) noexcept{
    data = other.data;
    len = other.len;
    capacity = other.capacity;

    //Make the moved rvalue empty  *IMPORTANT*
    other.data = nullptr;
    other.len = 0;
    other.capacity = 0;
}

MiniString& MiniString::operator= (const MiniString& other){
    //remember to check self-assign
    if(this==&other){
        return *this;
    }
    //remember to release old resourses
    delete[] data;
    len = other.len;
    capacity = other.capacity;//better to copy other member first to make error alignment
    data = new char[capacity];
    std::memcpy(data,other.data,capacity);
    return *this;
}

MiniString& MiniString::operator= (MiniString&& other) noexcept/*remember noexcept*/{
    //remember to check self-assign
    if(this==&other){
        return *this;
    }
    delete[] data;
    data = other.data;
    len = other.len;
    capacity = other.capacity;
    other.data = nullptr;
    other.len = 0;
    other.capacity = 0;
    return *this;
}

MiniString::~MiniString(){delete[] data;}//no need to operate len and capacity because they will die when the deconstructor ended 

std::size_t MiniString::size()const{
    return len;
}

const char* MiniString::c_str() const{
    return data?data : "";//need to handle nullptr
} 

void MiniString::push_back(char c){
    if(len+1 >= capacity){
        size_t newcap=(2*capacity>2) ? 2*capacity:2;
        auto newdata= new char[newcap];
        std::memcpy(newdata,data,len+1);
        delete[] data;
        data=newdata;
        capacity=newcap;
    }
    data[len]=c;
    data[len+1]='\0';
    len++;
}