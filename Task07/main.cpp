#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
class Complex {
    double re_,im_;
public:
    Complex():re_(0),im_(0){} Complex(double r):re_(r),im_(0){} Complex(double r,double i):re_(r),im_(i){}
    double real()const{return re_;} double imag()const{return im_;} double magnitude()const{return std::hypot(re_,im_);}
    Complex operator+(const Complex& b)const{return {re_+b.re_,im_+b.im_};}
    Complex operator-(const Complex& b)const{return {re_-b.re_,im_-b.im_};}
    Complex operator*(const Complex& b)const{return {re_*b.re_-im_*b.im_,re_*b.im_+im_*b.re_};}
    Complex operator/(const Complex& b)const{double d=b.re_*b.re_+b.im_*b.im_;if(d==0)throw std::domain_error("division by zero impedance");return {(re_*b.re_+im_*b.im_)/d,(im_*b.re_-re_*b.im_)/d};}
    bool operator==(const Complex& b)const{return re_==b.re_&&im_==b.im_;}
    friend std::ostream& operator<<(std::ostream& os,const Complex& z){return os<<std::fixed<<std::setprecision(2)<<z.re_<<(z.im_<0?" - j":" + j")<<std::abs(z.im_)<<" ohm";}
};
Complex parallel(const Complex& a,const Complex& b){return a*b/(a+b);}
int main(){const Complex resistor(10),inductor(0,5),capacitor(0,-10);Complex series=resistor+inductor+capacitor;Complex par=parallel(resistor,inductor);std::cout<<"Series RLC: "<<series<<", |Z|="<<series.magnitude()<<" ohm\n";std::cout<<"Parallel R-L: "<<par<<"\n";try{auto invalid=resistor/Complex();(void)invalid;}catch(const std::domain_error& e){std::cout<<"Safe error: "<<e.what()<<'\n';}}

