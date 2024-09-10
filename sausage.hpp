#pragma once

#include <iostream>
#include <stddef.h>
#include <stdexcept>
#include <ostream>
#include <vector>

namespace sausage
{
    template <typename T> class link
    {

    public:
        virtual T value() const = 0;
        virtual link<T>* next() const = 0;

        virtual bool empty() const = 0;
        virtual size_t size() const = 0;

        virtual const link<T>* get(const size_t index) const = 0;
        virtual T get_value(const size_t index) const = 0;

        void print() const
        {
            print_to(std::cout);
        }

        virtual void print_to(std::ostream& stream) const = 0;
    
    protected:
        static T get_first(const T* values, const size_t length)
        {
            if (length == 0)
            {
                throw std::invalid_argument("Cannot initialize a link with an empty list");
            }

            return values[0];
        }

        static T get_first(const std::vector<T>& values)
        {
            if (values.empty())
            {
                throw std::invalid_argument("Cannot initialize a link with an empty list");
            }

            return values[0];
        }

        virtual void print_to_internal(std::ostream& stream) const = 0;

    };

    template <typename T> class single_link : public link<T>
    {

    public:
        single_link(const T value) :
            _value(value), _next(nullptr) {}

        single_link(const T value, single_link<T>* next) :
            _value(value), _next(next) {}
        
        single_link(const T* values, const size_t length) :
            _value(link<T>::get_first(values, length)), _next(nullptr)
        {
            for (size_t i = length - 1; i > 0; i--)
            {
                _next = new single_link<T>(values[i], _next);
            }
        }
        
        single_link(const std::vector<T>& values) :
            _value(link<T>::get_first(values)), _next(nullptr)
        {
            for (size_t i = values.size() - 1; i > 0; i--)
            {
                _next = new single_link<T>(values[i], _next);
            }
        }
        
        T value() const override
        {
            return _value;
        }

        link<T>* next() const override
        {
            return _next;
        }
        
        bool empty() const override
        {
            return false;
        }

        size_t size() const override
        {
            if (_next)
            {
                return 1 + _next->size();
            }

            return 1;
        }

        const link<T>* get(const size_t index) const override
        {
            const link<T>* current = this;

            for (size_t i = 0; i < index; i++)
            {
                current = current->next();

                if (!current)
                {
                    throw std::out_of_range("Index out of range");
                }
            }

            return current;
        }

        T get_value(const size_t index) const override
        {
            const link<T>* current = this;

            for (size_t i = 0; i < index; i++)
            {
                current = current->next();

                if (!current)
                {
                    throw std::out_of_range("Index out of range");
                }
            }

            return current->value();
        }

        void print_to(std::ostream& stream) const override
        {
            stream << "( " << _value;

            if (_next)
            {
                _next->print_to_internal(stream);
            }

            stream << " )";
        }

    protected:
        void print_to_internal(std::ostream& stream) const override
        {
            stream << " -> " << _value;

            if (_next)
            {
                _next->print_to_internal(stream);
            }
        }
    
        const T _value;

        single_link<T>* _next;

    };
}
