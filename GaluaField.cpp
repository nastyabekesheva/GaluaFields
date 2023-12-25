//
//  GaluaField.cpp
//  GF
//
//  Created by Nastya Bekesheva on 06.12.2023.
//

#include "GaluaField.hpp"

GaluaField::GaluaField(FieldElement &generator)
{
    _generator = generator;
}

FieldElement GaluaField::add(FieldElement &a, FieldElement &b)
{
    FieldElement res;
    for (std::size_t i = 0; i < a.size(); ++i)
    {
        res.set((a[i] ^ b[i]), i);
    }
    
    return res;
}

FieldElement GaluaField::mul(FieldElement &a, FieldElement &b)
{
    FieldElement res;
    
    FieldElement ac(a);
    
    for (int i = 0; i < _extension; ++i)
    {
        if (b.getbit(i) == 1)
            res = add(res, ac);
        ac = shift_one(ac);
        //std::cout << to_bin(ac) << std::endl;
    }
    
    return res;
}

FieldElement GaluaField::square(FieldElement &a)
{
    /*FieldElement res;
    std::cout << to_bin(res) << std::endl;
    for (int i = 0; i < _extension/2; ++i)
    {
        res.setbit(a.getbit(i), 2*i);
        std::cout << to_bin(res) << std::endl;

        res.setbit(0, 2*i+1);
        
        std::cout << to_bin(res) << std::endl;

    }
    
    return res;*/
    
    return mul(a, a);
}

FieldElement GaluaField::pow(FieldElement &a,  FieldElement &b)
{
    FieldElement result("1");
    for (int i = bit_length(b) - 1; i >= 0; --i)
    {
        result = square(result);
        if (b.getbit(i) == 1)
        {
            result = mul(a, result);
        }
    }
    
    return result;
}

FieldElement GaluaField::inverse(FieldElement &a)
{
    FieldElement e("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110");
    return  pow(a, e);
}

FieldElement GaluaField::trace(FieldElement &a)
{
    FieldElement result = a;
    FieldElement tmp = a;
    
    for (std::size_t i = 1; i < _extension; ++i)
    {
        tmp = square(tmp);
        result = add(result, tmp);
    }
    
    return result;
}


FieldElement GaluaField::shift_one(FieldElement &a)
{
    FieldElement result;
    
    result.set((a[0] << (uint64_t)1), 0);
    
    for (int i = 1; i <= 2; ++i)
    {
        result.set(((a[i] << (uint64_t)1) ^ ((a[i-1] >> (uint64_t)63) & (uint64_t)1)), i);
    }
    
    if (result.getbit(_extension) == 1)
        result = add(result, _generator);
    
    return result;
}

FieldElement GaluaField::neu_add()
{
    return FieldElement("0");
}

FieldElement GaluaField::neu_mul()
{
    return FieldElement("1");
}

std::size_t GaluaField::bit_length(FieldElement &a)
{
    int k = a.size() - 1;
    
    while (a[k] == 0 && k >= 0)
    {
        --k;
    }
    
    if (k < 0)
        return 1;
    else
    {
        std::size_t j = 0;
        uint64_t b = a[k];
        
        while (b != 0)
        {
            ++j;
            b = b / 2;
        }
        
        return (j+64*(k));
        //return j;
    }
    
    
}

std::string GaluaField::to_bin(FieldElement &a)
{
    //std::size_t i = bit_length(a);
    
    std::string result = "";
    /*for (int i = 0; i < 2; ++i)
    {
        result += std::to_string(a.getbit(j));
    }
    
    
    
    if (result.size() < 173)
    {
        std::size_t k = 173 - result.size() - 2;
        std::string tmp = std::string(k, '0');
        return tmp + result;
        
        
    }*/
    
    for (int i = 172; i >= 0; --i)
    {
        result += std::to_string(a.getbit(i));
    }
    
    
    
    
    return result;
}
