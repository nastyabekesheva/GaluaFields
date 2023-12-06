//
//  GaluaField.hpp
//  GF
//
//  Created by Nastya Bekesheva on 06.12.2023.
//

#ifndef GaluaField_hpp
#define GaluaField_hpp

#include "FieldElement.hpp"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>

class GaluaField
{
private:
    unsigned int _extension = 173;
    FieldElement _generator;
    
public:
    GaluaField(FieldElement &generator);
    FieldElement add(FieldElement &a, FieldElement &b);
    FieldElement mul(FieldElement &a, FieldElement &b);
    FieldElement pow(FieldElement &a, FieldElement &b);
    FieldElement square(FieldElement &a);
    FieldElement inverse(FieldElement &a);
    FieldElement trace(FieldElement &a);
    FieldElement neu_add();
    FieldElement neu_mul();
    
    FieldElement shift_one(FieldElement &a);
    std::size_t bit_length(FieldElement &a);
    std::string to_bin(FieldElement &a);
};

#endif /* GaluaField_hpp */
