#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
class student{
    private:
    std::string name_;
    int id_;
    int age_;
    std::vector<int> grades_;
    public:
    student():name_(""),id_(0),age_(0){}
    student(std::string name_input,int id_input,int age_input,std::vector<int> grades_input):name_(name_input),id_(id_input),age_(age_input),grades_(grades_input){}
    student(const student& other):name_(other.name_),id_(other.id_),age_(other.age_),grades_(other.grades_){}
    ~student(){
        std::cout<<"Destructor called for student:"<<name_<<std::endl;
    }
    student& operator=(const student& other);
    void addGrade(int g);
    double getAverage() const;
    void displayInfo() const;
    void setName(const std::string& newName);
    void setAge(int newAge);
    void setId(int newId);
    void removeGrade(int index);
};
//operator equal achievement
student& student::operator=(const student& other)
{
    if(this == &other)
    {
        return *this;
    }
    name_ = other.name_;
    id_ = other.id_;
    age_ = other.age_;
    grades_ = other.grades_;
    return *this;
}


//add on function
void student::addGrade(int g)
{
    if(g>=0 && g<=100)
    {
        grades_.push_back(g);
    }
    else
    {
        std::cout<<"Grade mark invalid!"<<std::endl;
    }
}

//compute average score
double student::getAverage() const
{
    if(!grades_.empty())
    {
        return std::accumulate(grades_.begin(),grades_.end(),0.0)/grades_.size();
    }
    else
    {
        return 0.0;
    }    
}

//display function
void student::displayInfo() const
{
    std::cout<<"Name: "<<name_<<std::endl;
    std::cout<<"ID: "<<id_<<", "<<"Age: "<<age_<<std::endl;
    std::cout<<"Grades: ";
    for(auto num:grades_)
    {
        std::cout<<num<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Average: "<<getAverage()<<std::endl;

}

//PERSONAL INFORMATION UPDATE SECTION
void student::setName(const std::string& newName)
{
    name_ = newName;
}
void student::setAge(int newAge)
{
    age_ = newAge;
}
void student::setId(int newId)
{
    id_=newId;
}

//Delete certain grade(use index as parameter)
void student::removeGrade(int index)
{
    if(0<=index && index<grades_.size())//it is illegal to write *0<=index<grades_.size()*
    {
        grades_.erase(grades_.begin()+index);
    }
    else
    {
        std::cout<<"Invalid index!"<<std::endl;
    }
}
