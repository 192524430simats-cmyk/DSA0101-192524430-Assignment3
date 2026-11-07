#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
struct Time { int seconds=0; Time& operator++(){++seconds;return *this;} Time operator++(int){Time old=*this;++*this;return old;} bool operator==(const Time& b)const{return seconds==b.seconds;} bool operator<(const Time& b)const{return seconds<b.seconds;} std::string format()const{std::ostringstream os;os<<std::setfill('0')<<std::setw(2)<<seconds/3600<<':'<<std::setw(2)<<(seconds/60)%60<<':'<<std::setw(2)<<seconds%60;return os.str();} };
class Playlist { std::vector<std::string> tracks_; public: explicit Playlist(std::vector<std::string> t):tracks_(std::move(t)){} std::string& operator[](std::size_t i){if(i>=tracks_.size())throw std::out_of_range("track index");return tracks_[i];} const std::string& operator[](std::size_t i)const{if(i>=tracks_.size())throw std::out_of_range("track index");return tracks_[i];} std::size_t size()const{return tracks_.size();} };
int main(){Time t{5};Time a=t++;Time b=++t;std::cout<<a.seconds<<' '<<b.seconds<<' '<<t.seconds<<'\n';Time rollover{3599};++rollover;std::cout<<"Rollover: "<<rollover.format()<<'\n';Playlist p({"Intro","Song","Outro"});std::cout<<"Now playing: "<<p[1]<<'\n';try{std::cout<<p[static_cast<std::size_t>(-1)];}catch(const std::out_of_range&){std::cout<<"Invalid playlist index\n";}}

