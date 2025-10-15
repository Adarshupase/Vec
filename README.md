#  Vec
<br>
*A simple Vector implementation* <br>

## currently supports<br>
1. `primitive types`<br>
2. `push_back({..})`<br>
3. `size()`<br>
4. `collapse()`<br>
5. `Random access`<br>
6. `Multidimensional arrays with simple declaration`<br>
7. `support for Complex types like structs and classes`<br>


## todo
1. `arena allocation`<br>
2. `shuffle function to randomize the array`<br>

## Usage Example

A simple example using `Vec`:<br>
```collapse()``` helps you clear up the Vec
```cpp
#include "../Vec.hpp"

int main() 
{
    Vec<Vec<float>> fVec = {{2.4f,4.3f,0.0f},{3.0f,5.2221f}};
    fVec.collapse();
}
```
<br>


```sub``` is used to extract the sub Vector withing the vector

```cpp
#include "../Vec.hpp"
int main()
{
    Vec<Vec<int>> vec{{1,2,3},{4,5,6},{7,5,8},{9,10,11}};
    Vec<Vec<int>> subvec = vec.sub(1,2);
    std::cout << subvec << '\n';
    
}
```




