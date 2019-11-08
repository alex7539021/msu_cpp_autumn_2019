#ifndef BigInt_H
#define BigInt_H

#include <iostream>
#include <cstdlib>

class BigInt {

    int *data_;
    unsigned int size_;
    int sign_;

public:

    BigInt();
    BigInt(const int64_t N);
    BigInt(const BigInt& B);
    
    BigInt& operator=(const int64_t N);
    BigInt& operator=(const BigInt& B);
    
    friend std::ostream& operator<<(std::ostream &out, const BigInt &B);
    
    BigInt operator+(const BigInt& B) const;
    BigInt operator-(const BigInt& B) const;
    BigInt operator-() const;
    bool operator==(const BigInt& B) const;
    bool operator!=(const BigInt& B) const;
    bool operator>(const BigInt& B) const; 
    bool operator>=(const BigInt& B) const;
    bool operator<(const BigInt& B) const;
    bool operator<=(const BigInt& B) const;

    ~BigInt();
};

std::ostream& operator<<(std::ostream &out, const BigInt &B);

#endif