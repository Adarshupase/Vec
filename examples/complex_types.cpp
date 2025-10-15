
#include "../Vec.hpp"

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
}
 
