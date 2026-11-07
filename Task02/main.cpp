#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Prescription {
    int n_;
    std::string* medicines_;
public:
    explicit Prescription(int count) : n_(count < 0 ? 0 : count), medicines_(new std::string[static_cast<std::size_t>(n_)]) {}
    Prescription(const Prescription& other) : n_(other.n_), medicines_(new std::string[static_cast<std::size_t>(n_)]) {
        for (int i=0; i<n_; ++i) medicines_[i]=other.medicines_[i];
    }
    Prescription& operator=(const Prescription& other) {
        if (this != &other) { auto* fresh=new std::string[static_cast<std::size_t>(other.n_)];
            for (int i=0; i<other.n_; ++i) fresh[i]=other.medicines_[i];
            delete[] medicines_; medicines_=fresh; n_=other.n_; }
        return *this;
    }
    ~Prescription() { delete[] medicines_; }
    void set(int i,const std::string& m){ medicines_[i]=m; }
    const std::string& get(int i) const { return medicines_[i]; }
    int size() const { return n_; }
};

void inspectByValue(Prescription p) { std::cout << "value parameter has " << p.size() << " medicines\n"; }
void inspectByReference(const Prescription& p) { std::cout << "const reference has " << p.size() << " medicines\n"; }
int main() {
    Prescription p(2); p.set(0,"Paracetamol"); p.set(1,"ORS");
    Prescription q=p; q.set(1,"Cetirizine"); Prescription r(1); r=p; p.set(0,"Ibuprofen"); r=r;
    std::cout << p.get(0)<<' '<<p.get(1)<<" | "<<q.get(0)<<' '<<q.get(1)<<" | "<<r.get(0)<<' '<<r.get(1)<<'\n';
    inspectByValue(p); inspectByReference(p);
    std::vector<std::string> valueBased{"Aspirin","ORS"}; auto independent=valueBased; independent[0]="Ibuprofen";
    std::cout << "vector original=" << valueBased[0] << ", copy=" << independent[0] << '\n';
}

