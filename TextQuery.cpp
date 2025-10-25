#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <memory>
class QueryResult{//store the result of search (asshole class完全的多余)
    friend std::ostream &print(std::ostream &os,const QueryResult &qr);
    public:
    QueryResult(std::string s,std::shared_ptr<std::vector<std::string>> a,std::shared_ptr<std::set<int>> b):wts(s),filecopy(a),LineNoSet(b){}
    private:
    std::string wts;//word to search
    //share the same memory same data 
    std::shared_ptr<std::vector<std::string>> filecopy;
    std::shared_ptr<std::set<int>> LineNoSet;//Line number reflect set
};
std::ostream &print(std::ostream &os,const QueryResult &qr);
class TextQuery{//read and build map
    public:
    TextQuery(std::ifstream &ifs);
    QueryResult query(const std::string &wts)const;//implement the search process
    private:
    std::shared_ptr<std::vector<std::string>> filecopy;
    std::map<std::string,std::shared_ptr<std::set<int>>> record;
};
int main(){
    std::ifstream textfile("News.txt");
    TextQuery tq(textfile);
    while(true){
        std::cout<<"Enter the word u want to search(Enter 0 to quit): ";
        std::string wts;
        std::cin>>wts;
        if(wts=="0"){break;}
        print(std::cout,tq.query(wts))<<std::endl;
    }
    textfile.close();
    return 0;
}
TextQuery::TextQuery(std::ifstream &ifs){
    std::string textline;
    filecopy=std::make_shared<std::vector<std::string>>();
    while(std::getline(ifs,textline)){
        filecopy->push_back(textline);
        int n=filecopy->size()-1;
        std::istringstream is(textline);
        std::string word;
        while(is>>word){
            auto &wordptr =record[word];
            if(!wordptr){
                wordptr.reset(new std::set<int>);
            }
            wordptr->insert(n);
        }
    }
}
QueryResult TextQuery::query(const std::string &wts)const{
    static std::shared_ptr<std::set<int>> empty(new std::set<int>);//If not found return this
    auto loc=record.find(wts);
    if(loc==record.cend()){
        return QueryResult(wts,filecopy,empty);
    }
    else{
        return QueryResult(wts,filecopy,loc->second);
    }
}
std::ostream &print(std::ostream &os,const QueryResult &qr){
    os<<qr.wts<<" occurs "<<qr.LineNoSet->size()<<" time(s)"<<std::endl;
    for(auto index:*qr.LineNoSet){
        os<<"\t(line"<<index+1<<") "<<*(qr.filecopy->begin()+index)<<std::endl;
    }
    return os;
}
