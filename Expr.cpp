#include <iostream>
#include <memory>
#include <string>
//抽象基类
class Expr_base{
    public: 
    virtual ~Expr_base()=default;
    //抽象接口
    virtual double eval() const=0;
    virtual std::string rep() const=0;
};
//数字类
class NumberExpr : public Expr_base{
    private:
    double value;
    public:
    explicit NumberExpr(double v):value(v){}
    double eval() const override{
        return value;
    }
    std::string rep() const override{
        return std::to_string(value);
    }
};

//Expr多态句柄类，包装shared_ptr
class Expr{
    private:
    std::shared_ptr<Expr_base> ptr;//实现多态，不需要知道里面存的是哪个派生类，接口更干净
    public:
    Expr(double v):ptr(std::make_shared<NumberExpr>(v)){}
    Expr(std::shared_ptr<Expr_base> p):ptr(std::move(p)){}
    double eval() const{
        return ptr->eval();
    }
    std::string rep() const{
        return ptr->rep();
    }
};
//-符号表达式类，这个类需要适配所有的多态句柄，也就是不论是什么数字也好表达式也好。。。都可以取负
class UnaryMinusExpr : public Expr_base{
    private:
    Expr expr;
    public:
    explicit UnaryMinusExpr(const Expr& e):expr(e){}
    double eval() const override{
        return -expr.eval();
    }
    std::string rep() const override{
        return "-(" + expr.rep() +")";
    }
};
//二元运算的父类，作为所有二元运算的基础
class BinaryExpr : public Expr_base{
    protected:
    Expr lhs;
    Expr rhs;
    std::string op;//用于rep（）输出
    BinaryExpr(const Expr& l, const Expr& r, std::string op_symbol):lhs(l),rhs(r),op(op_symbol){}
    public:
    std::string rep() const override{
        return "("+lhs.rep()+" "+op+" "+rhs.rep()+")";
    }
};
//加法节点，加法派生类
class AddExpr : public BinaryExpr{
    public:
    AddExpr(const Expr& l,const Expr& r):BinaryExpr(l,r,"+"){}
    double eval() const override{
        return lhs.eval()+rhs.eval();
    }
};  
class SubExpr : public BinaryExpr{
    public:
    SubExpr(const Expr& l,const Expr& r):BinaryExpr(l,r,"-"){}
    double eval() const override{
        return lhs.eval()-rhs.eval();
    }
};
class MulExpr : public BinaryExpr{
    public:
    MulExpr(const Expr& l,const Expr& r):BinaryExpr(l,r,"*"){}
    double eval() const override{
        return lhs.eval() * rhs.eval();
    }
};
class DivExpr : public BinaryExpr{
    public:
    DivExpr(const Expr& l,const Expr& r):BinaryExpr(l,r,"/"){}
    double eval() const override{
        return lhs.eval() / rhs.eval();
    }
};

//负号重载，全局作用域，不是放在类内
Expr operator-(const Expr& e){
    return Expr(std::make_shared<UnaryMinusExpr>(e));
}
//加号重载，全局作用域
Expr operator+(const Expr& a,const Expr& b){
    return Expr(std::make_shared<AddExpr>(a,b));
}
Expr operator-(const Expr& a,const Expr& b){
    return Expr(std::make_shared<SubExpr>(a,b));
}
Expr operator*(const Expr& a,const Expr& b){
    return Expr(std::make_shared<MulExpr>(a,b));
}
Expr operator/(const Expr& a,const Expr& b){
    return Expr(std::make_shared<DivExpr>(a,b));
}
//主函数
int main(){
    Expr x=5;
    Expr y=2;
    Expr a=x + y;
    Expr b=x - y;
    Expr c=x * y;
    Expr d=x / y;
    std::cout<<"a="<<a.rep()<<"="<<a.eval()<<std::endl;
    std::cout<<"b="<<b.rep()<<"="<<b.eval()<<std::endl;
    std::cout<<"c="<<c.rep()<<"="<<c.eval()<<std::endl;
    std::cout<<"d="<<d.rep()<<"="<<d.eval()<<std::endl;
    system("pause");
    return 0;
}