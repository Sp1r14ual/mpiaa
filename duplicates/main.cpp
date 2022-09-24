#include "duplicates.h"

#define CATCH_CONFIG_RUNNER
#include "../catch.hpp"

#include "duplicates_test.cpp"
int main(int argc, char **argv) {
    int result = Catch::Session().run(argc, argv);
    return result;
}
