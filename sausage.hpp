#pragma once

#include <iostream>
#include <ostream>

namespace sausage
{
    template <typename T> class link
    {

    public:
        link(T value, link* next) :
            value(value), next(next) {}
        
        void print_to(std::ostream& stream) const
        {
            stream << value;

            if (next)
            {
                stream << " -> ";

                next->print_to(stream);
            }
        }

        void print() const
        {
            print_to(std::cout);
        }
    
    private:
        T value;
        link* next;

    };

    template <typename T> class list
    {
        
    public:
        void print_to(std::ostream& stream) const
        {
            stream << "( ";

            if (links)
            {
                links->print_to(stream);
            }

            stream << " )\n";
        }

        void print() const
        {
            print_to(std::cout);
        }

    private:
        link<T>* links;

    };
}
