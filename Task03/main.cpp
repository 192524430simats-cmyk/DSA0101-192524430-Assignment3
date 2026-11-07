#include <iostream>
#include <memory>
#include <vector>

class Event {
    int rows_, seats_;
    std::vector<std::unique_ptr<bool[]>> map_;
public:
    Event(int rows,int seats):rows_(rows<0?0:rows),seats_(seats<0?0:seats) {
        map_.reserve(static_cast<std::size_t>(rows_));
        for(int r=0;r<rows_;++r) map_.push_back(std::make_unique<bool[]>(static_cast<std::size_t>(seats_)));
        std::cout<<"Event opened "<<rows_<<'x'<<seats_<<'\n';
    }
    ~Event(){std::cout<<"Event closed "<<rows_<<'x'<<seats_<<'\n';}
    bool book(int r,int s){if(r<0||r>=rows_||s<0||s>=seats_||map_[r][s]) return false; map_[r][s]=true;return true;}
    bool cancel(int r,int s){if(r<0||r>=rows_||s<0||s>=seats_||!map_[r][s])return false;map_[r][s]=false;return true;}
};
int main(){
    Event stackEvent(2,3); std::cout<<"stack booked="<<stackEvent.book(0,1)<<'\n';
    { Event blockEvent(1,2); blockEvent.book(0,0); }
    Event* heapEvent=new Event(1,1); heapEvent->book(0,0); delete heapEvent;
    Event emptyEvent(0,5); std::cout<<"zero-row booking="<<emptyEvent.book(0,0)<<'\n';
}

