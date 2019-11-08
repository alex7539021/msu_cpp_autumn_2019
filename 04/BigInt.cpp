#include "BigInt.h"

BigInt::BigInt() : data_(nullptr), size_(0), sign_(1) {}

BigInt::BigInt(int64_t N) {
    data_ = nullptr;
    size_ = 0;
    sign_ = 1;

    int k = N;

    if (N < 0) {
        sign_ = -1;
        k = -N;
    }
    while (k > 0) {
        size_++;
        int *buf_data = new int[size_];
        std::copy(data_, data_ + size_ - 1, buf_data);
        buf_data[size_ - 1] = k % 10;
        delete[] data_;
        data_ = new int[size_];
        std::copy(buf_data, buf_data + size_, data_);
        delete[] buf_data;
        k /= 10;
    }
}

BigInt::BigInt(const BigInt& B) {
    data_ = nullptr;
    size_ = B.size_;
    sign_ = B.sign_;

    data_ = new int[size_];
    std::copy(B.data_, B.data_ + size_, data_);
}

BigInt& BigInt::operator=(const int64_t N) {
    BigInt buf(N);
    *this = buf;
    return *this;
}

BigInt& BigInt::operator=(const BigInt& B) {
    if (this == &B) {
        return *this;
    }
    size_ = B.size_;
    sign_ = B.sign_;

    delete[] data_;
    data_ = new int[size_];
    std::copy(B.data_, B.data_ + size_, data_);

    return *this;
}

BigInt BigInt::operator+(const BigInt& B) const {
    BigInt buf(*this);

    int dec = 0;
    if (B.sign_ == buf.sign_) {
        for (std::size_t i = 0; i < buf.size_ && i < B.size_ || dec; ++i) {
            if (i == buf.size_) {
                buf.size_++;
                int *buf_data = new int[buf.size_];
                std::copy(buf.data_, buf.data_ + buf.size_ - 1, buf_data);
                buf_data[buf.size_ - 1] = 0;
                delete[] buf.data_;
                buf.data_ = new int[buf.size_];
                std::copy(buf_data, buf_data + buf.size_, buf.data_);
                delete[] buf_data;
            }
            buf.data_[i] += dec + (i < B.size_ ? B.data_[i] : 0);
            dec = buf.data_[i] >= 10;
            if (dec) {
                buf.data_[i] -= 10;
            }
        }
    } else {
        if (buf.sign_ == 1) {
            buf = buf - (-B);
        } else {
            buf = B - (-buf);
        }
    }
    return buf;
}

BigInt BigInt::operator-(const BigInt& B) const {
    BigInt buf1(*this);
    BigInt buf2(B);
    bool sign = false;
    if (*this < B) {
        BigInt buf(buf1);
        buf1 = buf2;
        buf2 = buf;
        sign = true;
    }

    int dec = 0;
    if (buf1.sign_ == buf2.sign_) {
        for (std::size_t i = 0; i < buf2.size_ || dec; ++i) {
            buf1.data_[i] -= dec + (i < buf2.size_ ? buf2.data_[i] : 0);
            dec = buf1.data_[i] < 0;
            if (dec) {
                buf1.data_[i] += 10;
            }
        }
        while (buf1.size_ > 1 && buf1.data_[buf1.size_ - 1] == 0) {
            buf1.size_--;
            int *buf_data = new int[buf1.size_];
            std::copy(buf1.data_, buf1.data_ + buf1.size_, buf_data);
            delete[] buf1.data_;
            buf1.data_ = new int[buf1.size_];
            std::copy(buf_data, buf_data + buf1.size_, buf1.data_);
            delete[] buf_data;
        }

    } else {
        if (buf1.sign_ == 1) {
            buf1 = buf1 + (-buf2);
        } else {
            buf1 = (-buf1) + buf2;
        }
    }
    if (sign) {
        buf1.sign_ = -1;
    }
    return buf1;
}

bool BigInt::operator>(const BigInt& B) const {
    if (sign_ > B.sign_) {
        return true;
    }
    if (sign_ < B.sign_) {
        return false;
    }
    if (size_ > B.size_) {
        if (sign_ == 1) {
            return true;
        } else {
            return false;
        }
    }
    if (size_ < B.size_) {
        if (sign_ == 1) {
            return false;
        } else {
            return true;
        }
    }
    for (int i = size_ - 1; i >= 0; --i) {
        if ((sign_ == 1 && data_[i] > B.data_[i]) || (sign_ == -1 && data_[i] < B.data_[i] )) {
            return true;
        }
        if ((sign_ == 1 && data_[i] < B.data_[i]) || (sign_ == -1 && data_[i] > B.data_[i] )) {
            return false;
        }
        if (i == 0) {
            return false;
        }
    }
}

bool BigInt::operator>=(const BigInt& B) const {
    if (*this > B || *this == B) {
        return true;
    } else {
        return false;
    }
}

bool BigInt::operator<(const BigInt& B) const {
    if (*this >= B) {
        return false;
    } else {
        return true;
    }
}

bool BigInt::operator<=(const BigInt& B) const {
    if (*this > B) {
        return false;
    } else {
        return true;
    }
}

bool BigInt::operator==(const BigInt& B) const {
    if ((sign_ != B.sign_) || (size_ != B.size_)) {
        return false;
    }
    for (int i = size_ - 1; i >= 0; --i) {
        if (data_[i] != B.data_[i]) {
            return false;
        }
        if (i == 0) {
            return true;
        }
    }
}

bool BigInt::operator!=(const BigInt& B) const {
    if (*this == B) {
        return false;
    } else {
        return true;
    }
}

BigInt BigInt::operator-() const {
    BigInt buf(*this);
    buf.sign_ *= -1;
    return buf;
}

std::ostream& operator<<(std::ostream &out, const BigInt &B) {
    if (B.size_ != 0) {
        if (B.sign_ == -1) {
            out << '-';
        }
        for (int i = B.size_ - 1; i >= 0; --i) {
            out << B.data_[i];
        }
    } else {
        out << 0;
    }
    return out;
}


BigInt::~BigInt() {
    delete[] data_;
    data_ = nullptr;
}