#include <iostream>
#include <algorithm>
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

        void printVec(void)
        {
            for(T* itr = m_container_start; itr != m_current_unused_ptr;++itr)
            {
                std::cout << *(itr) << '\n';
            }
        }

        Vec() : m_container_start(nullptr),
                m_current_unused_ptr(nullptr),
                m_container_end(nullptr),
                m_size(0) {}

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
        void push_back(std::initializer_list<T> list)
        {
            int size_of_list = list.size();
            resize_if_neccessary(size_of_list);
            if(m_current_unused_ptr + size_of_list > m_container_end)
            {
                resize(size_of_list);
            }
            T* list_ptr = m_current_unused_ptr;
            
            for(const T &x :list)
            {
                *(list_ptr++) = x;
            }
            use(size_of_list);
            

        }
        void pop_back()
        {
            if(size > 0)
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
            if(m_size - elements_to_remove >= 0)
            {
                m_current_unused_ptr -= elements_to_remove;
                m_size -= elements_to_remove;
            }
            else
            {
                printf("Error while removing elements from an empty Vec");
                exit(1);
            }
        }
        
        


        size_t size()
        {
            return m_size;
        }
        ~Vec() {
        delete[] m_container_start;
        }



        
       

    private:
        T* m_container_start;
        T* m_current_unused_ptr;
        T* m_container_end;
        size_t m_size;
        std::allocator<T> m_allocator;
        
        void resize(size_t size_of_list)
        {
            size_t resize_length = predict_size(m_size,size_of_list);

            // m_container_start_temp = new T(resize_length);

            // std::copy(m_container_start,m_container_end,m_current_unused_ptr,m_container_start_temp);

            // delete m_container_start;
            // m_container_start = m_container_temp;
            // m_current_unused_ptr = m_container_start + size;
            // m_container_end = m_container_start + resize_length;
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

int main()
{
    Vec<int> myVec{{1,2,34}};
    myVec.push_back({3,4,5,6,54,2});
    myVec.printVec();
    myVec.collapse();
    myVec.size();
    myVec.printVec();


}
/*
variadic functions 
https://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c
*/