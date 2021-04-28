#include "NumberWithUnits.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>



const float TOLERANCE =0.001;

namespace ariel
{
    std::map<std::string, std::map<std::string, double >> convert_units;
    
    NumberWithUnits::NumberWithUnits(double d, std::string u)
    {
        if(convert_units.count(u)== 1) 
        {
            num=d;
            unit=u;
        }
        else
        {
            throw invalid_argument("illigal type");
        }

    }

    void NumberWithUnits::read_units(ifstream &file){
        if (file)
            {
                std::string line;
                while (getline(file, line))
                {
                    std::string first_unit, second_unit;
                    int digit = 1;
                    double tmp_dub = 0;
                    char equal;
                    istringstream(line) >> skipws >> digit>> first_unit >> equal >> tmp_dub >> second_unit;

                    if (convert_units.count(first_unit) == 0) //first_unit not exist
                    {
                        convert_units.insert({first_unit, map<std::string, double>{}});
                    }

                    if (convert_units.count(second_unit) == 0) //second_unit not exist
                    {
                        convert_units.insert({second_unit, map<std::string, double>{}});
                    }


                    for (auto const & element: convert_units.at(first_unit))
                    {
                        convert_units.at(element.first).insert({second_unit, tmp_dub / element.second});
                        convert_units.at(second_unit).insert({element.first, element.second / tmp_dub});
                    }          

                    for (auto const &element : convert_units.at(second_unit))
                    {
                        convert_units.at(element.first).insert({first_unit, 1 / (tmp_dub * element.second)});
                        convert_units.at(first_unit).insert({element.first, element.second * tmp_dub});
                    }

                        
                    
                    convert_units.at(first_unit).insert({second_unit,tmp_dub});
                    convert_units.at(second_unit).insert({second_unit,1/tmp_dub});
                }
            }
            else{
                throw invalid_argument("File not found");
            }   

    }

    NumberWithUnits NumberWithUnits::convert(double t_num,std::string t_unit,double n_num, std::string n_unit) const
    {
        if (convert_units.at(t_unit).count(n_unit) == 0)
        {
            throw invalid_argument("illigal type");
        }
        return NumberWithUnits(n_num*convert_units[t_unit][n_unit] , t_unit);
    }

    //matemtic operator +
    //
        NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &n)const
        {
            
            return NumberWithUnits((this->num+convert(this->num,this->unit,n.num,n.unit).num),this->unit);
        }

        NumberWithUnits NumberWithUnits::operator+=(const NumberWithUnits &n)
    {
        this->num += convert(this->num,this->unit,n.num,n.unit).num;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator+()
    {
        return NumberWithUnits(abs(this->num),this->unit);
    }
    // -
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &n) const
    {
        return NumberWithUnits(this->num-convert(this->num,this->unit,n.num,n.unit).num,this->unit);
    }
    NumberWithUnits NumberWithUnits::operator-=(const NumberWithUnits &n)
    {
        this->num -= convert(this->num,this->unit,n.num,n.unit).num;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator-() const
    {
        return NumberWithUnits(-abs(this->num),this->unit);
    }

    //comper operator
    bool NumberWithUnits::operator==(const NumberWithUnits &n) const
    {
        auto other_num = convert(this->num,this->unit,n.num,n.unit).num;
        return (abs(this->num-other_num)<=TOLERANCE);
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits &other) const    { return (!(*this==other)); }

    bool NumberWithUnits::operator<=(const NumberWithUnits &other) const    { return ((*this==other) || (*this<other));} 
                                                                                                                                                                                                                                                                                                                                                                                                                                    
    bool NumberWithUnits::operator>=(const NumberWithUnits &other) const    { return ((*this==other) || (*this>other)); }

    bool NumberWithUnits::operator<(const NumberWithUnits &n) const     { return this->num < convert(this->num,this->unit,n.num,n.unit).num; }

    bool NumberWithUnits::operator>(const NumberWithUnits &n) const     { return this->num > convert(this->num,this->unit,n.num,n.unit).num; }

    //perfix\postfix
    NumberWithUnits &NumberWithUnits::operator++()
    {
        this->num++;
        return *this ;
    }
    const NumberWithUnits NumberWithUnits::operator++(int flag)
    {
        double n = this->num;
        this->num++;
        return NumberWithUnits(n,this->unit);
    }
    NumberWithUnits &NumberWithUnits::operator--()
    {
        this->num--;
        return *this ;
    }
    const NumberWithUnits NumberWithUnits::operator--(int flag)
    {
        double n = this->num;
        this->num--;
        return NumberWithUnits(n,this->unit);
    }
    // multi
    NumberWithUnits operator*(double d, const NumberWithUnits& n) { return n*d; }

    NumberWithUnits NumberWithUnits::operator*(const double d) const { return NumberWithUnits(this->num*d,this->unit); }
    //input output

    std::ostream&operator<<(ostream &os, const NumberWithUnits &n) { return os << n.num << "[" << n.unit << "]"; }

    std::istream& operator>>(istream &is, NumberWithUnits &n)
    {
        int temp_num;
        std::string temp_unit;
        char space,open,close;
        is >> skipws >> temp_num >> space >> open >> temp_unit >> close;

        if (convert_units.count(temp_unit)==0)
        {
            throw invalid_argument("illigal type");
        }

        n.num=temp_num;
        n.unit=temp_unit;

        return is;
    }   
};

