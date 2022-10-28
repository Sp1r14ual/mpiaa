#include "closest_pair.h"

#define CATCH_CONFIG_RUNNER
#include "../catch.hpp"
#include "closest_pair_test.cpp"
#include "point_test.cpp"

int main(int argc, char **argv) {
    int result = Catch::Session().run(argc, argv);
    return result;
}
