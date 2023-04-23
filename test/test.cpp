#include "catch_amalgamated.hpp"
#include "../include/shared_ptr.hpp"

TEST_CASE("Test shared_ptr default constructor") {
    SECTION("Test shared_ptr<const int> default constructor") {
        shared_ptr<const int> ptr;
        REQUIRE(ptr.get() == nullptr);
    }

    SECTION("Test shared_ptr<int> default constructor") {
        shared_ptr<int> ptr;
        REQUIRE(ptr.get() == nullptr);
    }

    SECTION("Test shared_ptr<std::string> default constructor") {
        shared_ptr<std::string> ptr;
        REQUIRE(ptr.get() == nullptr);
    }
}

TEST_CASE("Test shared_ptr(const T object) constructor") {
    SECTION("Test shared_ptr<const int>(const T object) constructor") {
        const int expected_value = 5;
        shared_ptr<const int> ptr(expected_value);
        REQUIRE(*ptr == expected_value);
    }

    SECTION("Test shared_ptr<int>(const T object) constructor") {
        int expected_value = 5;
        shared_ptr<int> ptr(expected_value);
        REQUIRE(*ptr == expected_value);
    }

    SECTION("Test shared_ptr<std::string>(const T object) constructor") {
        std::string expected_value("hello world");
        shared_ptr<std::string> ptr(expected_value);
        REQUIRE(*ptr == expected_value);
    }
}

TEST_CASE("Test shared_ptr copy constructor") {
    SECTION("Test shared_ptr<const int> copy constructor") {
        const int expected_value = 5;
        shared_ptr<const int> first_ptr(expected_value);

        shared_ptr<const int> second_ptr(first_ptr);
        REQUIRE(*second_ptr == expected_value);
    }

    SECTION("Test shared_ptr<int> copy constructor") {
        int expected_value = 5;
        shared_ptr<int> first_ptr(expected_value);

        shared_ptr<int> second_ptr(first_ptr);
        REQUIRE(*second_ptr == expected_value);
    }

    SECTION("Test shared_ptr<std::string> copy constructor") {
        std::string expected_value("hello world");
        shared_ptr<std::string> first_ptr(expected_value);

        shared_ptr<std::string> second_ptr(first_ptr);
        REQUIRE(*second_ptr == expected_value);
    }
}

TEST_CASE("Test shared_ptr operator=") {
    SECTION("Test shared_ptr<int> operator=") {
        int expected_value = 5;
        shared_ptr<int> first_ptr(expected_value);
        shared_ptr<int> second_ptr;

        second_ptr = first_ptr;
        REQUIRE(*second_ptr == expected_value);
    }

    SECTION("Test shared_ptr<std::string> operator=") {
        std::string expected_value("hello world");
        shared_ptr<std::string> first_ptr(expected_value);
        shared_ptr<std::string> second_ptr;

        second_ptr = first_ptr;
        REQUIRE(*second_ptr == expected_value);
    }
}

TEST_CASE("Test shared_ptr with shared ownership") {
    SECTION("Test shared_ptr<int> with shared ownership") {
        shared_ptr<int> *base_ptr = new shared_ptr<int>(5);
        REQUIRE(base_ptr->use_count() == 1);

        {
            shared_ptr<int> second_ptr(*base_ptr);
            REQUIRE(base_ptr->use_count() == 2);
            
            {
                shared_ptr<int> third_ptr(second_ptr);
                REQUIRE(base_ptr->use_count() == 3);
            }
            REQUIRE(base_ptr->use_count() == 2);
        }
        REQUIRE(base_ptr->use_count() == 1);

        delete base_ptr;
        REQUIRE(base_ptr->use_count() == 0);
    }

    SECTION("Test shared_ptr<std::string> with shared ownership") {
        shared_ptr<std::string> *base_ptr = new shared_ptr<std::string>("hello world");
        REQUIRE(base_ptr->use_count() == 1);

        {
            shared_ptr<std::string> second_ptr(*base_ptr);
            REQUIRE(base_ptr->use_count() == 2);
            
            {
                shared_ptr<std::string> third_ptr(second_ptr);
                REQUIRE(base_ptr->use_count() == 3);
            }
            REQUIRE(base_ptr->use_count() == 2);
        }
        REQUIRE(base_ptr->use_count() == 1);

        delete base_ptr;
        REQUIRE(base_ptr->use_count() == 0);
    }
}
