#include <iostream>
#include <algorithm>
#include <unordered_map>
#define predict_size(x,y) ((x) + (y) + (y))



// we need a large pool at the start decoupled from other 
// objects 

template <typename T>
class Vec {
    public:
        void collapse()
        {
            if (m_container_start) {
                delete[] m_container_start;
                m_container_start = nullptr;
            }
            m_current_unused_ptr = nullptr;
            m_container_end = nullptr;
            m_size = 0;
        }

        Vec() : m_container_start(nullptr),
                m_current_unused_ptr(nullptr),
                m_container_end(nullptr),
                m_size(0) {}

        Vec(size_t size)
            :m_container_start(nullptr),
            m_current_unused_ptr(nullptr),
            m_container_end(nullptr),
            m_size(0)
            {
                reserve(size);

            } 
        
        Vec(std::initializer_list<T> list)
            : m_container_start(nullptr),
            m_current_unused_ptr(nullptr),
            m_container_end(nullptr),
            m_size(0)
            {
                size_t size_of_initializer = list.size();
                reserve(size_of_initializer);
                push_back(list);
            }

        
        Vec(const Vec& other)
            : m_container_start(nullptr),
              m_current_unused_ptr(nullptr),
              m_container_end(nullptr),
              m_size(0)
        {
            if (other.m_size > 0) {
                reserve(other.capacity());
                std::copy(other.m_container_start, other.m_container_start + other.m_size, m_container_start);
                m_size = other.m_size;
                m_current_unused_ptr = m_container_start + m_size;
            }
        }
        Vec(Vec&& other) noexcept
                : m_container_start(other.m_container_start),
                m_current_unused_ptr(other.m_current_unused_ptr),
                m_container_end(other.m_container_end),
                m_size(other.m_size)
        {
            other.m_container_start = nullptr;
            other.m_current_unused_ptr = nullptr;
            other.m_container_end = nullptr;
            other.m_size = 0;
        }
        Vec& operator=(const Vec& other)
        {
            if(this != &other)
            {
                reserve(other.capacity());
                m_size = other.m_size;
                std::copy(other.m_container_start,other.m_container_start + other.m_size,m_container_start);
                m_current_unused_ptr = m_container_start + m_size;
            }
            return *this;
        }
        Vec& operator=(Vec&& other) noexcept {
            if (this != &other) {
                delete[] m_container_start;
                m_container_start = other.m_container_start;
                m_current_unused_ptr = other.m_current_unused_ptr;
                m_container_end = other.m_container_end;
                m_size = other.m_size;

                other.m_container_start = nullptr;
                other.m_current_unused_ptr = nullptr;
                other.m_container_end = nullptr;
                other.m_size = 0;
            }
            return *this;
        }
        void push_back(const T& element)
        {
            resize_if_neccessary(1);
            *m_current_unused_ptr = element;
            use(1);
        }
        void push_back(std::initializer_list<T> list)
        {
            int size_of_list = list.size();
            resize_if_neccessary(size_of_list);
            T* list_ptr = m_current_unused_ptr;
            
            for(const T &x :list)
            {
                *(list_ptr++) = x ;
            }
            use(size_of_list);
            

        }
        void pop_back()
        {
            if(m_size > 0)
            {
                unuse(1);
            }
            else {
                printf("Error while removing element from an empty Vec");
                exit(1);
            }
        }
        void pop_back(size_t elements_to_remove)
        {
            if(elements_to_remove <= m_size)
            {
                unuse(elements_to_remove);
            }
            else
            {
                printf("Error while removing elements from an empty Vec");
                exit(1);
            }
        }
        T& operator[](int index)
        {
            if(index < 0){
                index = m_size + index;

            }
            if(index < 0 || static_cast<size_t>(index) >= m_size){
                 printf("Index out of range\n");
                 exit(1);
            }

            return *(m_container_start + index);
        }
        Vec<T> sub(size_t start,size_t end)
        {
            if(start > end || start < 0 || static_cast<size_t>(end) > m_size)
            {
                printf("Invalid slice range [%zu:%zu]\n", start, end);
                exit(1);
            }
            Vec<T> slice ;
            slice.reserve(end - start);
            for(int i = start ; i < end ; ++i)
            {
                slice.push_back((*this)[i]);
            }
            return slice;
            
        }

        


        size_t size() const
        {
            return m_size;
        }
        size_t capacity() const
        {
            return m_container_end - m_container_start;
        }
        // overload std::cout to print Vec<T>,Vec<Vec<T>> etc... 
        friend std::ostream& operator<<(std::ostream& os , const Vec<T>& vec)
        {
            os << "[";
            for(size_t i = 0; i < vec.m_size; ++i)
            {
                os << vec.m_container_start[i];
                if(i != vec.m_size-1)
                    os << ",";

            }
            os << "]";
            return os;
        }
        T* begin() {return m_container_start;}
        T* end() {return m_container_start + m_size;};
        T* begin() const {return m_container_start;}
        T* end() const {return m_container_start + m_size;}
        ~Vec() {
            if (m_container_start)
                delete[] m_container_start;
        }



        
       

    private:
        T* m_container_start;
        T* m_current_unused_ptr;
        T* m_container_end;
        size_t m_size;
        
        void resize(size_t size_of_list)
        {
            size_t resize_length = predict_size(m_size,size_of_list);
            reserve(resize_length);

        }
        void resize_if_neccessary(size_t size_)
        {
            if(m_current_unused_ptr + size_ > m_container_end)
            {
                resize(size_);
            }
        }
        void use(size_t size_used)
        {
            m_current_unused_ptr += size_used;
            m_size += size_used;
        }
        void unuse(size_t size_claimed)
        {
            m_current_unused_ptr -= size_claimed;
            m_size -= size_claimed;
        }
        // reserve returns the start of the new allocated memory 
        // use advances the memory pointer to point to the utilized memory 
        void reserve(size_t reserved_size)
        {   
            T* m_container_start_temp = new T[reserved_size];
            if (m_container_start)
                std::copy(m_container_start, m_current_unused_ptr, m_container_start_temp);

            delete[] m_container_start;
            m_container_start = m_container_start_temp;
            m_current_unused_ptr = m_container_start + m_size;
            m_container_end = m_container_start + reserved_size;
        }
};

void dfs(int i,Vec<Vec<int>>& ans,Vec<int> &cur,Vec<int>& nums)
{
    if(i == nums.size())
    {
        ans.push_back(cur);
        return ;
    }
    cur.push_back(nums[i]);
    dfs(i+1,ans,cur,nums);
    cur.pop_back();
    dfs(i+1,ans,cur,nums);
}



Vec<Vec<int>> subsets(Vec<int>& nums)
{
    Vec<Vec<int>> ans;
    Vec<int> cur;
    dfs(0,ans,cur,nums);
    return ans;


}
typedef struct {
    std::string name;
    unsigned int age;
}Person;
class Animal{
    public:
        std::string m_name;
        unsigned int m_age;

};
int main()
{
    Person p{"Tom",45};
    Vec<Person *> persons;
    Animal dog{"Dog",12};
    Vec<Animal> animals;
    animals.push_back(dog);
    persons.push_back(&p);
    for(auto &p : persons)
    {
        std::cout << p->name << '\n';
        std::cout << p->age << '\n';
    }
    for(auto &a : animals)
    {
        std::cout << a.m_name << '\n';
        std::cout << a.m_age << '\n';
    }
    Vec<int> nums({1,2,3});
    Vec<Vec<int>> ans = subsets(nums);
    std::cout << "ans = " << ans << '\n';


}
/*
variadic functions 
https://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c
*/
