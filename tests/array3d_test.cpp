#include "../lib/Array3D.h"
#include "gtest/gtest.h"
#include <cstdlib>

static const size_t kConstValueInSizeOfArray = 32;

TEST(ValidityZeroSizesTestSuite, Test_1) {
    ASSERT_EXIT(Array3D array = Array3D(0, 0, 0), testing::ExitedWithCode(1), "Invalid sizes of array.");
}

TEST(ValidityZeroSizesTestSuite, Test_2) {
    ASSERT_EXIT(Array3D array = Array3D(0, 51, 3), testing::ExitedWithCode(1), "Invalid sizes of array.");
}

TEST(ValidityZeroSizesTestSuite, Test_3) {
    ASSERT_EXIT(Array3D array = Array3D(24, 100, 0), testing::ExitedWithCode(1), "Invalid sizes of array.");
}

TEST(ValidityZeroSizesTestSuite, Test_4) {
    ASSERT_EXIT(Array3D array = Array3D(15, 0, 31), testing::ExitedWithCode(1), "Invalid sizes of array.");
}

TEST(ValidityZeroSizesTestSuite, Test_5) {
    ASSERT_EXIT(Array3D array = Array3D(0, 0, 4), testing::ExitedWithCode(1), "Invalid sizes of array.");
}



TEST(ValidityNegativeSizesTestSuite, Test_1) {
    ASSERT_EXIT(Array3D array = Array3D(-3, -123, -57), testing::ExitedWithCode(1), "Invalid sizes of array.");
}

TEST(ValidityNegativeSizesTestSuite, Test_2) {
    ASSERT_EXIT(Array3D array = Array3D(-10, 51, 3), testing::ExitedWithCode(1), "Invalid sizes of array.");
}

TEST(ValidityNegativeSizesTestSuite, Test_3) {
    ASSERT_EXIT(Array3D array = Array3D(24, 100, -43), testing::ExitedWithCode(1), "Invalid sizes of array.");
}

TEST(ValidityNegativeSizesTestSuite, Test_4) {
    ASSERT_EXIT(Array3D array = Array3D(15, -1, 31), testing::ExitedWithCode(1), "Invalid sizes of array.");
}

TEST(ValidityNegativeSizesTestSuite, Test_5) {
    ASSERT_EXIT(Array3D array = Array3D(-23, -94, 4), testing::ExitedWithCode(1), "Invalid sizes of array.");
}



TEST(CorrectSizesTestSuite, Test_1) {
    ASSERT_NO_THROW(Array3D array = Array3D(10, 51, 72));
}

TEST(CorrectSizesTestSuite, Test_2) {
    ASSERT_NO_THROW(Array3D array = Array3D(1, 1, 1));
}

TEST(CorrectSizesTestSuite, Test_3) {
    ASSERT_NO_THROW(Array3D array = Array3D(321, 214, 5));
}

TEST(CorrectSizesTestSuite, Test_4) {
    ASSERT_NO_THROW(Array3D array = Array3D(5, 1, 124));
}

TEST(CorrectSizesTestSuite, Test_5) {
    ASSERT_NO_THROW(Array3D array = Array3D(6, 321, 7));
}



TEST(MemorySizeTestSuite, Test_1) {
    Array3D array = Array3D(3, 20, 17);
    ASSERT_LE(sizeof(array), ((3 * 20 * 17) * 17 + 7) / 8 + kConstValueInSizeOfArray);
}

TEST(MemorySizeTestSuite, Test_2) {
    Array3D array = Array3D(132, 45, 10);
    ASSERT_LE(sizeof(array), ((132 * 45 * 10) * 17 + 7) / 8 + kConstValueInSizeOfArray);
}

TEST(MemorySizeTestSuite, Test_3) {
    Array3D array = Array3D(1, 1, 1);
    ASSERT_LE(sizeof(array), ((1 * 1 * 1) * 17 + 7) / 8 + kConstValueInSizeOfArray);
}

TEST(MemorySizeTestSuite, Test_4) {
    Array3D array = Array3D(15, 20, 3);
    ASSERT_LE(sizeof(array), ((15 * 20 * 3) * 17 + 7) / 8 + kConstValueInSizeOfArray);
}

TEST(MemorySizeTestSuite, Test_5) {
    Array3D array = Array3D(333, 171, 259);
    ASSERT_LE(sizeof(array), ((333 * 171 * 259) * 17 + 7) / 8 + kConstValueInSizeOfArray);
}



TEST(InputValueTestSuite, Test_1) {
    Array3D array = Array3D(12, 34, 7);
    array[7][18][3] = 213;
    ASSERT_EQ(static_cast<uint32_t> (array[7][18][3]), 213);
}

TEST(InputValueTestSuite, Test_2) {
    Array3D array = Array3D(1, 1, 1);
    array[0][0][0] = 1;
    ASSERT_EQ(static_cast<uint32_t> (array[0][0][0]), 1);
}

TEST(InputValueTestSuite, Test_3) {
    Array3D array = Array3D(32, 78, 25);
    array[31][77][24] = 10315;
    ASSERT_EQ(static_cast<uint32_t> (array[31][77][24]), 10315);
}

TEST(InputValueTestSuite, Test_4) {
    Array3D array = Array3D(42, 16, 93);
    array[23][3][56] = 6532;
    ASSERT_EQ(static_cast<uint32_t> (array[23][3][56]), 6532);
}

TEST(InputValueTestSuite, Test_5) {
    Array3D array = Array3D(18, 3, 25);
    array[1][2][0] = 999;
    ASSERT_EQ(static_cast<uint32_t> (array[1][2][0]), 999);
}



TEST(CopyConstructorTestSuite, Test_1) {
    Array3D array_original = Array3D(1, 1, 1);

    for (int i = 0; i < array_original.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_original.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_original.GetThirdDimension(); ++k) {
                array_original[i][j][k] = rand() % ((1 << 17) - 1) + 1;
            }
        }
    }

    Array3D array_copy = array_original;

    ASSERT_EQ(array_original, array_copy);
}

TEST(CopyConstructorTestSuite, Test_2) {
    Array3D array_original = Array3D(17, 32, 25);

    for (int i = 0; i < array_original.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_original.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_original.GetThirdDimension(); ++k) {
                array_original[i][j][k] = rand() % ((1 << 17) - 1) + 1;
            }
        }
    }

    Array3D array_copy = array_original;

    ASSERT_EQ(array_original, array_copy);
}

TEST(CopyConstructorTestSuite, Test_3) {
    Array3D array_original = Array3D(53, 13, 1);

    for (int i = 0; i < array_original.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_original.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_original.GetThirdDimension(); ++k) {
                array_original[i][j][k] = rand() % ((1 << 17) - 1) + 1;
            }
        }
    }

    Array3D array_copy = array_original;

    ASSERT_EQ(array_original, array_copy);
}

TEST(CopyConstructorTestSuite, Test_4) {
    Array3D array_original = Array3D(43, 56, 19);

    for (int i = 0; i < array_original.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_original.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_original.GetThirdDimension(); ++k) {
                array_original[i][j][k] = rand() % ((1 << 17) - 1) + 1;
            }
        }
    }

    Array3D array_copy = array_original;

    ASSERT_EQ(array_original, array_copy);
}

TEST(CopyConstructorTestSuite, Test_5) {
    Array3D array_original = Array3D(10, 10, 10);

    for (int i = 0; i < array_original.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_original.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_original.GetThirdDimension(); ++k) {
                array_original[i][j][k] = rand() % ((1 << 17) - 1) + 1;
            }
        }
    }

    Array3D array_copy = array_original;

    ASSERT_EQ(array_original, array_copy);
}



TEST(AssignmentOperatorTestSuite, Test_1) {
    Array3D array_original = Array3D(1, 1, 1);

    for (int i = 0; i < array_original.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_original.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_original.GetThirdDimension(); ++k) {
                array_original[i][j][k] = rand() % ((1 << 17) - 1) + 1;
            }
        }
    }

    Array3D array_new = Array3D(1, 1, 1);
    array_new = array_original;

    ASSERT_EQ(array_original, array_new);
}

TEST(AssignmentOperatorTestSuite, Test_2) {
    Array3D array_original = Array3D(17, 32, 25);

    for (int i = 0; i < array_original.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_original.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_original.GetThirdDimension(); ++k) {
                array_original[i][j][k] = rand() % ((1 << 17) - 1) + 1;
            }
        }
    }

    Array3D array_new = Array3D(2, 32, 43);
    array_new = array_original;

    ASSERT_EQ(array_original, array_new);
}

TEST(AssignmentOperatorTestSuite, Test_3) {
    Array3D array_original = Array3D(53, 13, 1);

    for (int i = 0; i < array_original.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_original.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_original.GetThirdDimension(); ++k) {
                array_original[i][j][k] = rand() % ((1 << 17) - 1) + 1;
            }
        }
    }

    Array3D array_new = Array3D(65, 54, 3);
    array_new = array_original;

    ASSERT_EQ(array_original, array_new);
}

TEST(AssignmentOperatorTestSuite, Test_4) {
    Array3D array_original = Array3D(43, 56, 19);

    for (int i = 0; i < array_original.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_original.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_original.GetThirdDimension(); ++k) {
                array_original[i][j][k] = rand() % ((1 << 17) - 1) + 1;
            }
        }
    }

    Array3D array_new = Array3D(45, 2, 42);
    array_new = array_original;

    ASSERT_EQ(array_original, array_new);
}

TEST(AssignmentOperatorTestSuite, Test_5) {
    Array3D array_original = Array3D(10, 10, 10);

    for (int i = 0; i < array_original.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_original.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_original.GetThirdDimension(); ++k) {
                array_original[i][j][k] = rand() % ((1 << 17) - 1) + 1;
            }
        }
    }

    Array3D array_new = Array3D(78, 23, 25);
    array_new = array_original;

    ASSERT_EQ(array_original, array_new);
}



TEST(AdditionOperatorTestSuite, Test_1) {
    Array3D array_1 = Array3D(23, 6, 72);
    Array3D array_2 = Array3D(23, 6, 71);

    ASSERT_EXIT(array_1 + array_2, testing::ExitedWithCode(1), "Arrays have different sizes.");
}

TEST(AdditionOperatorTestSuite, Test_2) {
    Array3D array_1 = Array3D(23, 6, 72);
    Array3D array_2 = Array3D(23, 6, 72);

    int*** correct_result = new int**[array_1.GetFirstDimension()];

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        correct_result[i] = new int*[array_1.GetSecondDimension()];
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            correct_result[i][j] = new int[array_1.GetThirdDimension()];
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                int element_1 = rand() % ((1 << 17) - 1) + 1;
                int element_2 = rand() % ((1 << 17) - 1 - element_1) + 1;
                correct_result[i][j][k] = element_1 + element_2;

                array_1[i][j][k] = element_1;
                array_2[i][j][k] = element_2;
            }
        }
    }

    Array3D result = array_1 + array_2;

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                if (correct_result[i][j][k] != static_cast<uint32_t> (result[i][j][k])) {
                    FAIL();
                }
            }
            delete[] correct_result[i][j];
        }
        delete[] correct_result[i];
    }

    delete[] correct_result;

    SUCCEED();
}

TEST(AdditionOperatorTestSuite, Test_3) {
    Array3D array_1 = Array3D(100, 63, 71);
    Array3D array_2 = Array3D(100, 63, 71);

    int*** correct_result = new int**[array_1.GetFirstDimension()];

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        correct_result[i] = new int*[array_1.GetSecondDimension()];
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            correct_result[i][j] = new int[array_1.GetThirdDimension()];
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                int element_1 = rand() % ((1 << 17) - 1) + 1;
                int element_2 = rand() % ((1 << 17) - 1 - element_1) + 1;
                correct_result[i][j][k] = element_1 + element_2;

                array_1[i][j][k] = element_1;
                array_2[i][j][k] = element_2;
            }
        }
    }

    Array3D result = array_1 + array_2;

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                if (correct_result[i][j][k] != static_cast<uint32_t> (result[i][j][k])) {
                    FAIL();
                }
            }
            delete[] correct_result[i][j];
        }
        delete[] correct_result[i];
    }

    delete[] correct_result;

    SUCCEED();
}

TEST(AdditionOperatorTestSuite, Test_4) {
    Array3D array_1 = Array3D(3, 25, 17);
    Array3D array_2 = Array3D(3, 25, 17);

    int*** correct_result = new int**[array_1.GetFirstDimension()];

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        correct_result[i] = new int*[array_1.GetSecondDimension()];
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            correct_result[i][j] = new int[array_1.GetThirdDimension()];
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                int element_1 = rand() % ((1 << 17) - 1) + 1;
                int element_2 = rand() % ((1 << 17) - 1 - element_1) + 1;
                correct_result[i][j][k] = element_1 + element_2;

                array_1[i][j][k] = element_1;
                array_2[i][j][k] = element_2;
            }
        }
    }

    Array3D result = array_1 + array_2;

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                if (correct_result[i][j][k] != static_cast<uint32_t> (result[i][j][k])) {
                    FAIL();
                }
            }
            delete[] correct_result[i][j];
        }
        delete[] correct_result[i];
    }

    delete[] correct_result;

    SUCCEED();
}

TEST(AdditionOperatorTestSuite, Test_5) {
    Array3D array_1 = Array3D(45, 31, 9);
    Array3D array_2 = Array3D(45, 31, 9);

    int*** correct_result = new int**[array_1.GetFirstDimension()];

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        correct_result[i] = new int*[array_1.GetSecondDimension()];
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            correct_result[i][j] = new int[array_1.GetThirdDimension()];
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                int element_1 = rand() % ((1 << 17) - 1) + 1;
                int element_2 = rand() % ((1 << 17) - 1 - element_1) + 1;
                correct_result[i][j][k] = element_1 + element_2;

                array_1[i][j][k] = element_1;
                array_2[i][j][k] = element_2;
            }
        }
    }

    Array3D result = array_1 + array_2;

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                if (correct_result[i][j][k] != static_cast<uint32_t> (result[i][j][k])) {
                    FAIL();
                }
            }
            delete[] correct_result[i][j];
        }
        delete[] correct_result[i];
    }

    delete[] correct_result;

    SUCCEED();
}



TEST(SubtractionOperatorTestSuite, Test_1) {
    Array3D array_1 = Array3D(23, 6, 72);
    Array3D array_2 = Array3D(23, 6, 71);

    ASSERT_EXIT(array_1 - array_2, testing::ExitedWithCode(1), "Arrays have different sizes.");
}

TEST(SubtractionOperatorTestSuite, Test_2) {
    Array3D array_1 = Array3D(23, 6, 72);
    Array3D array_2 = Array3D(23, 6, 72);

    int*** correct_result = new int**[array_1.GetFirstDimension()];

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        correct_result[i] = new int*[array_1.GetSecondDimension()];
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            correct_result[i][j] = new int[array_1.GetThirdDimension()];
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                int element_1 = rand() % ((1 << 17) - 1) + 1;
                int element_2 = rand() % ((1 << 17) - 1) + 1;
                correct_result[i][j][k] = std::max(element_1, element_2) - std::min(element_1, element_2);

                array_1[i][j][k] = std::max(element_1, element_2);
                array_2[i][j][k] = std::min(element_1, element_2);
            }
        }
    }

    Array3D result = array_1 - array_2;

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                if (correct_result[i][j][k] != static_cast<uint32_t> (result[i][j][k])) {
                    FAIL();
                }
            }
            delete[] correct_result[i][j];
        }
        delete[] correct_result[i];
    }

    delete[] correct_result;

    SUCCEED();
}

TEST(SubtractionOperatorTestSuite, Test_3) {
    Array3D array_1 = Array3D(100, 63, 71);
    Array3D array_2 = Array3D(100, 63, 71);

    int*** correct_result = new int**[array_1.GetFirstDimension()];

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        correct_result[i] = new int*[array_1.GetSecondDimension()];
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            correct_result[i][j] = new int[array_1.GetThirdDimension()];
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                int element_1 = rand() % ((1 << 17) - 1) + 1;
                int element_2 = rand() % ((1 << 17) - 1) + 1;
                correct_result[i][j][k] = std::max(element_1, element_2) - std::min(element_1, element_2);

                array_1[i][j][k] = std::max(element_1, element_2);
                array_2[i][j][k] = std::min(element_1, element_2);
            }
        }
    }

    Array3D result = array_1 - array_2;

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                if (correct_result[i][j][k] != static_cast<uint32_t> (result[i][j][k])) {
                    FAIL();
                }
            }
            delete[] correct_result[i][j];
        }
        delete[] correct_result[i];
    }

    delete[] correct_result;

    SUCCEED();
}

TEST(SubtractionOperatorTestSuite, Test_4) {
    Array3D array_1 = Array3D(3, 25, 17);
    Array3D array_2 = Array3D(3, 25, 17);

    int*** correct_result = new int**[array_1.GetFirstDimension()];

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        correct_result[i] = new int*[array_1.GetSecondDimension()];
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            correct_result[i][j] = new int[array_1.GetThirdDimension()];
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                int element_1 = rand() % ((1 << 17) - 1) + 1;
                int element_2 = rand() % ((1 << 17) - 1) + 1;
                correct_result[i][j][k] = std::max(element_1, element_2) - std::min(element_1, element_2);

                array_1[i][j][k] = std::max(element_1, element_2);
                array_2[i][j][k] = std::min(element_1, element_2);
            }
        }
    }

    Array3D result = array_1 - array_2;

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                if (correct_result[i][j][k] != static_cast<uint32_t> (result[i][j][k])) {
                    FAIL();
                }
            }
            delete[] correct_result[i][j];
        }
        delete[] correct_result[i];
    }

    delete[] correct_result;

    SUCCEED();
}

TEST(SubtractionOperatorTestSuite, Test_5) {
    Array3D array_1 = Array3D(45, 31, 9);
    Array3D array_2 = Array3D(45, 31, 9);

    int*** correct_result = new int**[array_1.GetFirstDimension()];

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        correct_result[i] = new int*[array_1.GetSecondDimension()];
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            correct_result[i][j] = new int[array_1.GetThirdDimension()];
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                int element_1 = rand() % ((1 << 17) - 1) + 1;
                int element_2 = rand() % ((1 << 17) - 1) + 1;
                correct_result[i][j][k] = std::max(element_1, element_2) - std::min(element_1, element_2);

                array_1[i][j][k] = std::max(element_1, element_2);
                array_2[i][j][k] = std::min(element_1, element_2);
            }
        }
    }

    Array3D result = array_1 - array_2;

    for (int i = 0; i < array_1.GetFirstDimension(); ++i) {
        for (int j = 0; j < array_1.GetSecondDimension(); ++j) {
            for (int k = 0; k < array_1.GetThirdDimension(); ++k) {
                if (correct_result[i][j][k] != static_cast<uint32_t> (result[i][j][k])) {
                    FAIL();
                }
            }
            delete[] correct_result[i][j];
        }
        delete[] correct_result[i];
    }

    delete[] correct_result;

    SUCCEED();
}



TEST(MultiplicationOperatorTestSuite, Test_1) {
    Array3D array = Array3D(1, 1, 1);
    uint32_t multiple = 481;

    int*** correct_result = new int**[array.GetFirstDimension()];

    for (int i = 0; i < array.GetFirstDimension(); ++i) {
        correct_result[i] = new int*[array.GetSecondDimension()];
        for (int j = 0; j < array.GetSecondDimension(); ++j) {
            correct_result[i][j] = new int[array.GetThirdDimension()];
            for (int k = 0; k < array.GetThirdDimension(); ++k) {
                uint32_t element = rand() % (((1 << 17) - 1) / multiple) + 1;
                correct_result[i][j][k] = static_cast<int> (element * multiple);

                array[i][j][k] = element;
            }
        }
    }

    Array3D result = array * multiple;

    for (int i = 0; i < array.GetFirstDimension(); ++i) {
        for (int j = 0; j < array.GetSecondDimension(); ++j) {
            for (int k = 0; k < array.GetThirdDimension(); ++k) {
                if (correct_result[i][j][k] != static_cast<uint32_t> (result[i][j][k])) {
                    FAIL();
                }
            }
            delete[] correct_result[i][j];
        }
        delete[] correct_result[i];
    }

    delete[] correct_result;

    SUCCEED();
}

TEST(MultiplicationOperatorTestSuite, Test_2) {
    Array3D array = Array3D(23, 6, 72);
    uint32_t multiple = 23;

    int*** correct_result = new int**[array.GetFirstDimension()];

    for (int i = 0; i < array.GetFirstDimension(); ++i) {
        correct_result[i] = new int*[array.GetSecondDimension()];
        for (int j = 0; j < array.GetSecondDimension(); ++j) {
            correct_result[i][j] = new int[array.GetThirdDimension()];
            for (int k = 0; k < array.GetThirdDimension(); ++k) {
                uint32_t element = rand() % (((1 << 17) - 1) / multiple) + 1;
                correct_result[i][j][k] = static_cast<int> (element * multiple);

                array[i][j][k] = element;
            }
        }
    }

    Array3D result = array * multiple;

    for (int i = 0; i < array.GetFirstDimension(); ++i) {
        for (int j = 0; j < array.GetSecondDimension(); ++j) {
            for (int k = 0; k < array.GetThirdDimension(); ++k) {
                if (correct_result[i][j][k] != static_cast<uint32_t> (result[i][j][k])) {
                    FAIL();
                }
            }
            delete[] correct_result[i][j];
        }
        delete[] correct_result[i];
    }

    delete[] correct_result;

    SUCCEED();
}

TEST(MultiplicationOperatorTestSuite, Test_3) {
    Array3D array = Array3D(100, 63, 71);
    uint32_t multiple = 1093;

    int*** correct_result = new int**[array.GetFirstDimension()];

    for (int i = 0; i < array.GetFirstDimension(); ++i) {
        correct_result[i] = new int*[array.GetSecondDimension()];
        for (int j = 0; j < array.GetSecondDimension(); ++j) {
            correct_result[i][j] = new int[array.GetThirdDimension()];
            for (int k = 0; k < array.GetThirdDimension(); ++k) {
                uint32_t element = rand() % (((1 << 17) - 1) / multiple) + 1;
                correct_result[i][j][k] = static_cast<int> (element * multiple);

                array[i][j][k] = element;
            }
        }
    }

    Array3D result = array * multiple;

    for (int i = 0; i < array.GetFirstDimension(); ++i) {
        for (int j = 0; j < array.GetSecondDimension(); ++j) {
            for (int k = 0; k < array.GetThirdDimension(); ++k) {
                if (correct_result[i][j][k] != static_cast<uint32_t> (result[i][j][k])) {
                    FAIL();
                }
            }
            delete[] correct_result[i][j];
        }
        delete[] correct_result[i];
    }

    delete[] correct_result;

    SUCCEED();
}

TEST(MultiplicationOperatorTestSuite, Test_4) {
    Array3D array = Array3D(3, 25, 17);
    uint32_t multiple = 2;

    int*** correct_result = new int**[array.GetFirstDimension()];

    for (int i = 0; i < array.GetFirstDimension(); ++i) {
        correct_result[i] = new int*[array.GetSecondDimension()];
        for (int j = 0; j < array.GetSecondDimension(); ++j) {
            correct_result[i][j] = new int[array.GetThirdDimension()];
            for (int k = 0; k < array.GetThirdDimension(); ++k) {
                uint32_t element = rand() % (((1 << 17) - 1) / multiple) + 1;
                correct_result[i][j][k] = static_cast<int> (element * multiple);

                array[i][j][k] = element;
            }
        }
    }

    Array3D result = array * multiple;

    for (int i = 0; i < array.GetFirstDimension(); ++i) {
        for (int j = 0; j < array.GetSecondDimension(); ++j) {
            for (int k = 0; k < array.GetThirdDimension(); ++k) {
                if (correct_result[i][j][k] != static_cast<uint32_t> (result[i][j][k])) {
                    FAIL();
                }
            }
            delete[] correct_result[i][j];
        }
        delete[] correct_result[i];
    }

    delete[] correct_result;

    SUCCEED();
}

TEST(MultiplicationOperatorTestSuite, Test_5) {
    Array3D array = Array3D(45, 31, 9);
    uint32_t multiple = 277;

    int*** correct_result = new int**[array.GetFirstDimension()];

    for (int i = 0; i < array.GetFirstDimension(); ++i) {
        correct_result[i] = new int*[array.GetSecondDimension()];
        for (int j = 0; j < array.GetSecondDimension(); ++j) {
            correct_result[i][j] = new int[array.GetThirdDimension()];
            for (int k = 0; k < array.GetThirdDimension(); ++k) {
                uint32_t element = rand() % (((1 << 17) - 1) / multiple) + 1;
                correct_result[i][j][k] = static_cast<int> (element * multiple);

                array[i][j][k] = element;
            }
        }
    }

    Array3D result = array * multiple;

    for (int i = 0; i < array.GetFirstDimension(); ++i) {
        for (int j = 0; j < array.GetSecondDimension(); ++j) {
            for (int k = 0; k < array.GetThirdDimension(); ++k) {
                if (correct_result[i][j][k] != static_cast<uint32_t> (result[i][j][k])) {
                    FAIL();
                }
            }
            delete[] correct_result[i][j];
        }
        delete[] correct_result[i];
    }

    delete[] correct_result;

    SUCCEED();
}