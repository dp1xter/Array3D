#pragma once
#include <cstdint>
#include <iostream>

static const size_t kBitSizeNumbers = 17;
static const size_t kBitSizeByte = 8;

static void RaiseError(const char* message) {
    std::cerr << message;
    exit(EXIT_FAILURE);
}

class Number17Bit {

public:
    Number17Bit(uint8_t* const array_1d_, size_t index_x, size_t index_y, size_t index_z, size_t y, size_t z);

    Number17Bit& operator=(uint32_t value);

    explicit operator uint32_t() const;

    friend std::ostream& operator<<(std::ostream& stream, const Number17Bit& number);

    friend std::istream& operator>>(std::istream& stream, Number17Bit number);

private:
    size_t number_shift_in_byte_;

    uint8_t* pointer_to_number_;

    [[nodiscard]] uint32_t GetValue() const;

    void SetValue(uint32_t value);
};

class Array1D {

public:
    Array1D(uint8_t* const array_2d_, size_t index_x, size_t index_y, size_t y, size_t z);

    Number17Bit operator[](int32_t index_z) const;

private:
    size_t index_in_first_dimens_;
    size_t index_in_second_dimens_;
    size_t second_dimension_size_;
    size_t third_dimension_size_;

    uint8_t* array_1d_;
};

class Array2D {

public:
    Array2D(uint8_t* const array_3d_, size_t index_x, size_t y, size_t z);

    Array1D operator[](int32_t index_y) const;

private:
    size_t index_in_first_dimens_;
    size_t second_dimension_size_;
    size_t third_dimension_size_;

    uint8_t* array_2d_;
};

class Array3D {

public:
    Array3D(int32_t x, int32_t y, int32_t z);

    Array3D(const Array3D& other);

    static Array3D MakeArray(int32_t x, int32_t y, int32_t z);

    [[nodiscard]] size_t GetFirstDimension() const;

    [[nodiscard]] size_t GetSecondDimension() const;

    [[nodiscard]] size_t GetThirdDimension() const;

    Array2D operator[](int32_t index_x) const;

    friend bool operator==(const Array3D& lhs, const Array3D& rhs);

    friend Array3D operator+(const Array3D& lhs, const Array3D& rhs);

    friend Array3D operator-(const Array3D& lhs, const Array3D& rhs);

    friend Array3D operator*(const Array3D& array, uint32_t multiple);

    Array3D& operator=(const Array3D& rhs);

    friend std::ostream& operator<<(std::ostream& stream, const Array3D& array);

    friend std::istream& operator>>(std::istream& stream, Array3D& array);

    ~Array3D();

private:
    size_t first_dimension_size_;
    size_t second_dimension_size_;
    size_t third_dimension_size_;

    uint8_t* array_3d_;
};

