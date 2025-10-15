#include "../Vec.hpp"

int main() 
{
    Vec<Vec<float>> fVec = {{2.4f,4.3f,0.0f},{3.0f,5.2221f}};
    fVec.push_back({{3.4f},{4.5f}});
    fVec.push_back({{3.4f}});
    std::cout << "size before collapse : " << fVec.size() << '\n';
    std::cout << "capacity before collapse : " << fVec.capacity() << '\n';
    fVec.collapse();
    std::cout << "size after collapse : " << fVec.size() << '\n';
    std::cout << "capacity capacity collapse : " << fVec.capacity() << '\n';
}