#include "../catch.hpp"
#include <chrono>
#include <iostream>
#include "lcs.h"


TEST_CASE( "Both strings are empty" ) {
    auto t1 = std::chrono::high_resolution_clock::now();
    CHECK( lcs("", "") == "" );
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time: " << time << " sec." << std::endl;

}

TEST_CASE( "One string is empty" ) {
    auto t1 = std::chrono::high_resolution_clock::now();
    CHECK( lcs("", "abcd") == "" );
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time: " << time << " sec." << std::endl;
    t1 = std::chrono::high_resolution_clock::now();
    CHECK( lcs("abcd", "") == "" );
    t2 = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time: " << time << " sec." << std::endl;
}

TEST_CASE( "Equal strings" ) {
    auto t1 = std::chrono::high_resolution_clock::now();
    CHECK( lcs("abcd", "abcd") == "abcd" );
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time: " << time << " sec." << std::endl;
}

TEST_CASE( "Substring" ) {
    auto t1 = std::chrono::high_resolution_clock::now();
    CHECK( lcs("abab", "ab") == "ab" );
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time: " << time << " sec." << std::endl;
}

TEST_CASE( "Substring in the middle" ) {
    auto t1 = std::chrono::high_resolution_clock::now();
    CHECK( lcs("xyaban", "abarab") == "aba" );
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time: " << time << " sec." << std::endl;
}

TEST_CASE( "Subsequences" ) {
    auto t1 = std::chrono::high_resolution_clock::now();
    CHECK( lcs("nahybser", "iunkayxbis") == "naybs" );
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time: " << time << " sec." << std::endl;
    t1 = std::chrono::high_resolution_clock::now();
    CHECK( lcs("z1artunx", "yz21rx") == "z1rx" );
    t2 = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time: " << time << " sec." << std::endl;
    t1 = std::chrono::high_resolution_clock::now();
    CHECK( lcs("z1arxzyx1a", "yz21rx") == "z1rx" );
    t2 = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time: " << time << " sec." << std::endl;
    t1 = std::chrono::high_resolution_clock::now();
    CHECK( lcs("yillnum", "numyjiljil") == "yill" );
    t2 = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time: " << time << " sec." << std::endl;
}

TEST_CASE( "Reverse subsequence" ) {
    auto t1 = std::chrono::high_resolution_clock::now();
    auto result = lcs("xablar", "ralbax");
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time: " << time << " sec." << std::endl;
    CHECK( (result == "aba" || result == "ala") ); 
}
