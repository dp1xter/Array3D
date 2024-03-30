#include "Array3D.h"

Number17Bit::Number17Bit(uint8_t* const array_1d_, size_t index_x, size_t index_y, size_t index_z, size_t y, size_t z) {
    pointer_to_number_ = &array_1d_[((index_x * y * z + index_y * z + index_z) * kBitSizeNumbers) / kBitSizeByte];

    number_shift_in_byte_ = ((pointer_to_number_ - array_1d_) % kBitSizeNumbers + 1) / 2 % kBitSizeByte;
}

Number17Bit& Number17Bit::operator=(uint32_t value) {
    SetValue(value);

    return *this;
}

Number17Bit::operator uint32_t() const {
    return GetValue();
}

uint32_t Number17Bit::GetValue() const {
    return ((((*pointer_to_number_ & ((1 << (kBitSizeByte - number_shift_in_byte_)) - 1)) << (number_shift_in_byte_ + kBitSizeByte + 1)) |
            *(pointer_to_number_ + 1) << (number_shift_in_byte_ + 1)) |
            (*(pointer_to_number_ + 2) >> (kBitSizeByte - number_shift_in_byte_ - 1)));
}

void Number17Bit::SetValue(uint32_t value) {
    *(pointer_to_number_) |= static_cast<uint8_t> (value >> (kBitSizeByte + number_shift_in_byte_ + 1));
    *(pointer_to_number_ + 1) = static_cast<uint8_t> ((value & ((1 << (kBitSizeByte + number_shift_in_byte_ + 1)) - 1)) >> (number_shift_in_byte_ + 1));
    *(pointer_to_number_ + 2) |= static_cast<uint8_t> ((value & ((1 << (number_shift_in_byte_ + 1)) - 1)) << (kBitSizeByte - number_shift_in_byte_ - 1));
}

Array1D::Array1D(uint8_t* const array_2d_, size_t index_x, size_t index_y, size_t y, size_t z) {
    index_in_second_dimens_ = index_y;
    index_in_first_dimens_ = index_x;
    second_dimension_size_ = y;
    third_dimension_size_ = z;

    array_1d_ = array_2d_;
}

Number17Bit Array1D::operator[](int32_t index_z) const {
    if (index_z >= third_dimension_size_ || index_z < 0) {
        RaiseError("Invalid index of third dimension of array.");
    }

    return {array_1d_, index_in_first_dimens_, index_in_second_dimens_,
            static_cast<size_t> (index_z), second_dimension_size_, third_dimension_size_};
}

Array2D::Array2D(uint8_t* const array_3d_, size_t index_x, size_t y, size_t z) {
    index_in_first_dimens_ = index_x;
    second_dimension_size_ = y;
    third_dimension_size_ = z;

    array_2d_ = array_3d_;
}

Array1D Array2D::operator[](int32_t index_y) const {
    if (index_y >= second_dimension_size_ || index_y < 0) {
        RaiseError("Invalid index of second dimension of array.");
    }

    return {array_2d_, index_in_first_dimens_, static_cast<size_t> (index_y),
            second_dimension_size_, third_dimension_size_};
}

Array3D::Array3D(int32_t x, int32_t y, int32_t z) {
    if (x <= 0 || y <= 0 || z <= 0) {
        RaiseError("Invalid sizes of array.");
    }

    first_dimension_size_ = x;
    second_dimension_size_ = y;
    third_dimension_size_ = z;

    array_3d_ = new uint8_t[(x * y * z * kBitSizeNumbers + kBitSizeByte - 1) / kBitSizeByte]{0};
}

Array3D::Array3D(const Array3D& other) {
    first_dimension_size_ = other.first_dimension_size_;
    second_dimension_size_ = other.second_dimension_size_;
    third_dimension_size_ = other.third_dimension_size_;

    array_3d_ = new uint8_t[(first_dimension_size_ * second_dimension_size_ * third_dimension_size_ * kBitSizeNumbers + kBitSizeByte - 1) / kBitSizeByte];

    for (int i = 0; i < (first_dimension_size_ * second_dimension_size_ * third_dimension_size_ * kBitSizeNumbers + kBitSizeByte - 1) / kBitSizeByte; ++i) {
        array_3d_[i] = other.array_3d_[i];
    }
}

Array3D Array3D::MakeArray(int32_t x, int32_t y, int32_t z) {
    return {x, y, z};
}

Array3D::~Array3D() {
    delete[] array_3d_;
}

size_t Array3D::GetFirstDimension() const {
    return first_dimension_size_;
}

size_t Array3D::GetSecondDimension() const {
    return second_dimension_size_;
}

size_t Array3D::GetThirdDimension() const {
    return third_dimension_size_;
}

Array2D Array3D::operator[](int32_t index_x) const {
    if (index_x >= first_dimension_size_ || index_x < 0) {
        RaiseError("Invalid index of first dimension of array.");
    }

    return {array_3d_, static_cast<size_t> (index_x), second_dimension_size_, third_dimension_size_};
}

bool operator==(const Array3D& lhs, const Array3D& rhs) {
    if (lhs.first_dimension_size_ != rhs.first_dimension_size_ || lhs.second_dimension_size_ != rhs.second_dimension_size_ ||
        lhs.third_dimension_size_ != rhs.third_dimension_size_) {
        return false;
    }

    const size_t x = lhs.first_dimension_size_;
    const size_t y = lhs.second_dimension_size_;
    const size_t z = lhs.third_dimension_size_;

    for (int i = 0; i < (x * y * z * kBitSizeNumbers + kBitSizeByte - 1) / kBitSizeByte; ++i) {
        if (lhs.array_3d_[i] != rhs.array_3d_[i]) {
            return false;
        }
    }

    return true;
}

Array3D operator+(const Array3D& lhs, const Array3D& rhs) {
    if (lhs.first_dimension_size_ != rhs.first_dimension_size_ || lhs.second_dimension_size_ != rhs.second_dimension_size_ ||
        lhs.third_dimension_size_ != rhs.third_dimension_size_) {
        RaiseError("Arrays have different sizes.");
    }

    const size_t x = lhs.first_dimension_size_;
    const size_t y = lhs.second_dimension_size_;
    const size_t z = lhs.third_dimension_size_;

    Array3D result = Array3D(static_cast<int32_t> (x), static_cast<int32_t> (y), static_cast<int32_t> (z));
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                result[i][j][k] = static_cast<uint32_t> (lhs[i][j][k]) + static_cast<uint32_t> (rhs[i][j][k]);
            }
        }
    }

    return result;
}

Array3D operator-(const Array3D& lhs, const Array3D& rhs) {
    if (lhs.first_dimension_size_ != rhs.first_dimension_size_ || lhs.second_dimension_size_ != rhs.second_dimension_size_ ||
        lhs.third_dimension_size_ != rhs.third_dimension_size_) {
        RaiseError("Arrays have different sizes.");
    }

    const size_t x = lhs.first_dimension_size_;
    const size_t y = lhs.second_dimension_size_;
    const size_t z = lhs.third_dimension_size_;

    Array3D result = Array3D(static_cast<int32_t> (x), static_cast<int32_t> (y), static_cast<int32_t> (z));
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                result[i][j][k] = static_cast<uint32_t> (lhs[i][j][k]) - static_cast<uint32_t> (rhs[i][j][k]);
            }
        }
    }

    return result;
}

Array3D operator*(const Array3D& array, uint32_t multiple) {
    const size_t x = array.first_dimension_size_;
    const size_t y = array.second_dimension_size_;
    const size_t z = array.third_dimension_size_;

    Array3D result = Array3D(static_cast<int32_t> (x), static_cast<int32_t> (y), static_cast<int32_t> (z));
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                result[i][j][k] = static_cast<uint32_t> (array[i][j][k]) * multiple;
            }
        }
    }

    return result;
}

Array3D& Array3D::operator=(const Array3D& rhs) {
    if (this == &rhs) {
        return *this;
    }

    first_dimension_size_ = rhs.first_dimension_size_;
    second_dimension_size_ = rhs.second_dimension_size_;
    third_dimension_size_ = rhs.third_dimension_size_;

    delete[] array_3d_;

    array_3d_ = new uint8_t[(first_dimension_size_ * second_dimension_size_ * third_dimension_size_ * 17 + 7) / 8];

    for (int i = 0; i < (first_dimension_size_ * second_dimension_size_ * third_dimension_size_ * 17 + 7) / 8; ++i) {
        array_3d_[i] = rhs.array_3d_[i];
    }

    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Number17Bit& number) {
    stream << number.GetValue();
    
    return stream;
}

std::istream& operator>>(std::istream& stream, Number17Bit number) {
    uint32_t input_number;

    stream >> input_number;
    number.SetValue(input_number);

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Array3D& array) {
    for (int i = 0; i < array.first_dimension_size_; ++i) {
        for (int j = 0; j < array.second_dimension_size_; ++j) {
            for (int k = 0; k < array.third_dimension_size_; ++k) {
                stream << array[i][j][k] << " ";
            }
            stream << '\n';
        }
        stream << '\n';
    }

    return stream;
}

std::istream& operator>>(std::istream& stream, Array3D& array) {
    for (int i = 0; i < array.first_dimension_size_; ++i) {
        for (int j = 0; j < array.second_dimension_size_; ++j) {
            for (int k = 0; k < array.third_dimension_size_; ++k) {
                stream >> array[i][j][k];
            }
        }
    }

    return stream;
}
