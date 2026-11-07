#include <iomanip>
#include <iostream>
#include <stdexcept>

class Money {
    long long paise_;
public:
    explicit Money(long long rupees=0,int paise=0):paise_(rupees*100+paise){}
    static Money fromPaise(long long p){Money m; m.paise_=p; return m;}
    Money operator+(const Money& b)const{return fromPaise(paise_+b.paise_);}
    Money operator-(const Money& b)const{return fromPaise(paise_-b.paise_);}
    Money& operator+=(const Money& b){paise_+=b.paise_;return *this;}
    bool operator==(const Money& b)const{return paise_==b.paise_;}
    bool operator<(const Money& b)const{return paise_<b.paise_;}
    friend std::ostream& operator<<(std::ostream& os,const Money& m){auto v=m.paise_; if(v<0){os<<"-Rs ";v=-v;}else os<<"Rs ";return os<<v/100<<'.'<<std::setw(2)<<std::setfill('0')<<v%100<<std::setfill(' ');}
    friend std::istream& operator>>(std::istream& is,Money& m){long long r;char dot;int p;if(is>>r>>dot>>p){if(dot!='.')is.setstate(std::ios::failbit);else m=fromPaise(r*100+(r<0?-p:p));}return is;}
};
int main(){Money a(120,75),b(79,25);Money c=a+b;std::cout<<c<<'\n'<<std::boolalpha<<(c==Money(200))<<'\n';std::cout<<Money(0,75)+Money(0,50)<<'\n'<<Money(1)-Money(2)<<'\n';}

