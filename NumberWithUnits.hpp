#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

namespace ariel {
class NumberWithUnits {
   private:
    double num;
    string unit;

   public:
    
   // static map<std::string, map< std::string, double >> convert_units;

    NumberWithUnits(double d, string u);

    static void read_units(ifstream& units_file);
    NumberWithUnits convert(double t_num,std::string t_unit,double n_num, std::string n_unit)const;
    
      // equal and not-equal operators
    bool operator==(const NumberWithUnits& n) const;
    bool operator!=(const NumberWithUnits& n) const;

    // bigger-then and smaller-then operators
    bool operator>(const NumberWithUnits& n ) const ;
    bool operator<(const NumberWithUnits& n ) const ;

    // bigger-equal-then and smaller-ewual-then operators
    bool operator>=(const NumberWithUnits& n ) const  ;
    bool operator<=(const NumberWithUnits& n ) const  ;

    // plus and minus unary
    NumberWithUnits operator+();
    NumberWithUnits operator-() const;


// add and sub operators
    NumberWithUnits operator+(const NumberWithUnits& n) const;
    NumberWithUnits operator-(const NumberWithUnits& n) const;


    // add-equal, sub-equal operators
    NumberWithUnits operator+=(const NumberWithUnits& other);
    NumberWithUnits operator-=(const NumberWithUnits& other);


    // incriment operators
    NumberWithUnits& operator++();
    const NumberWithUnits operator++(int flagForPostfix);

    // decriment operators
    NumberWithUnits& operator--();
    const NumberWithUnits operator--(int flagForPostfix);

    
    
    // multiplication by double from left
    friend NumberWithUnits operator*(double num, const NumberWithUnits& n);

    // multiplication by double from right
    NumberWithUnits operator*(const double num)const;

    // output and input
    friend ostream& operator<<(ostream& os, const NumberWithUnits& n);
    friend istream& operator>>(istream& is, NumberWithUnits& n);
};
}  // namespace ariel
