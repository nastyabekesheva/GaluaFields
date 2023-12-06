//
//  FieldElement.cpp
//  FieldElement
//
//  Created by Nastya Bekesheva on 06.12.2023.
//

#include "FieldElement.hpp"

FieldElement::FieldElement()
{
    _coeffs = {0, 0, 0};
}

FieldElement::FieldElement(std::vector<uint64_t> c)
{
    if (c.size() != 3)
        throw "((((((";
    _coeffs = c;
}

FieldElement::FieldElement(std::string bin)
{
    _coeffs = {0, 0, 0};
    for (int i = bin.size() - 1; i >= 0; --i)
    {
        if (bin[i] == '1')
            setbit(bin.size() - 1 - i);
    }
}

uint64_t FieldElement::getbit(std::size_t i)
{
    uint64_t i_1 = i / 64;
    uint64_t i_2 = i % 64;
    
    return ((_coeffs[i_1] >> i_2) & 1);
}

void FieldElement::setbit(std::size_t i)
{
    uint64_t i_1 = i / 64;
    uint64_t i_2 = i % 64;
    
    _coeffs[i_1] = (_coeffs[i_1] | (1 << i_2));
}

std::vector<uint64_t> FieldElement::get_coeffs()
{
    return _coeffs;
}

std::size_t FieldElement::size()
{
    return _coeffs.size();
}

void FieldElement::push_back(uint64_t value)
{
    _coeffs.push_back(value);
}

uint64_t FieldElement::operator[](std::size_t i)
{
    return _coeffs[i];
}

void FieldElement::set(uint64_t value, std::size_t i)
{
    _coeffs[i] = value;
}

FieldElement::FieldElement(const FieldElement &other)
{
    _coeffs = other._coeffs;
}

