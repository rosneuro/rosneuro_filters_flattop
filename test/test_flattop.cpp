#include <gtest/gtest.h>
#include "Flattop.hpp"

namespace rosneuro {

class FlattopTestSuite : public ::testing::Test {
    public:
        FlattopTestSuite() {}
        ~FlattopTestSuite() {}
        void SetUp() { flattop_filter = new Flattop <double>(); }
        void TearDown() { delete flattop_filter; }
        Flattop <double>* flattop_filter;
    };

TEST_F(FlattopTestSuite, Constructor) {
    ASSERT_EQ(flattop_filter->name_, "flattop");
    ASSERT_FALSE(flattop_filter->is_window_set_);
}

TEST_F(FlattopTestSuite, Configure) {
    ASSERT_TRUE(flattop_filter->configure());
}

TEST_F(FlattopTestSuite, ApplyWithValidWindow) {
    DynamicMatrix<double> inputMatrix(3, 3);
    DynamicMatrix<double> result = flattop_filter->apply(inputMatrix);

    ASSERT_EQ(result.rows(), inputMatrix.rows());
    ASSERT_EQ(result.cols(), inputMatrix.cols());

    DynamicMatrix<double> expected(3, 3);
    expected << -1.95894e-313,            -0, -1.94889e+225,
                            0,   3.24249e-86,  1.47286e-319,
                -1.00703e+186,            -0,            -0;

    ASSERT_TRUE(result.isApprox(expected, 0.01));
}

TEST_F(FlattopTestSuite, ApplyWithoutWindow) {
    DynamicMatrix<double> inputMatrix(-1, 0);
    ASSERT_THROW(flattop_filter->apply(inputMatrix), std::bad_alloc);
}

TEST_F(FlattopTestSuite, CreateWindowWithValidSamples) {
    ASSERT_TRUE(flattop_filter->create_window(1));
}

TEST_F(FlattopTestSuite, CreateWindowWithInvalidSamples) {
    ASSERT_THROW(flattop_filter->create_window(-1), std::bad_alloc);
}

}

int main(int argc, char **argv) {
    ros::init(argc, argv, "test_flattop");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}