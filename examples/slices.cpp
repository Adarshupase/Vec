#include "../Vec.hpp"


int main()
{
    Vec<Vec<int>> vec{{1,2,3},{4,5,6},{7,5,8},{9,10,11}};
    Vec<Vec<int>> subvec = vec.sub(1,2);
    std::cout << subvec << '\n';
    

}