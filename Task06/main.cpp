#include <cstring>
#include <iostream>
#include <string>
class Text {
    char* data_;
public:
    explicit Text(const char* s=""):data_(new char[std::strlen(s)+1]){std::strcpy(data_,s);}
    Text(const Text& o):Text(o.data_){}
    Text& operator=(const Text& o){if(this!=&o){auto* p=new char[std::strlen(o.data_)+1];std::strcpy(p,o.data_);delete[] data_;data_=p;}return *this;}
    ~Text(){delete[] data_;}
    Text operator+(const Text& b)const{std::string joined(data_);joined+=b.data_;return Text(joined.c_str());}
    bool operator==(const Text& b)const{return std::strcmp(data_,b.data_)==0;}
    bool operator!=(const Text& b)const{return !(*this==b);}
    Text& operator+=(const Text& b){*this=*this+b;return *this;}
    friend std::ostream& operator<<(std::ostream& os,const Text& t){return os<<t.data_;}
};
int main(){Text a("Hello "),b("from "),c("C++");Text result=a+b+c;Text empty;Text longMessage("A deliberately longer SMS message for copy and concatenation checks.");a=a;std::cout<<result<<'\n'<<"empty=["<<empty<<"] long="<<longMessage<<" self="<<a<<'\n'<<std::boolalpha<<(result==Text("Hello from C++"))<<' '<<(result!=c)<<'\n';}

