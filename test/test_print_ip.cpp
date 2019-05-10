#include <catch2/catch.hpp>

#include <sstream>
#include <array>
#include <tuple>

#include <print_ip.h>

#include "utils.h"

using namespace std;
using namespace griha;
using namespace Catch::Matchers;

TEST_CASE("print_ip") {
    ostringstream os;
    SECTION("integral types") {
        print_ip(os, static_cast<char>(0));
        REQUIRE_THAT(os.str(), Equals("0"s));

        os.str(""s);
        print_ip(os, static_cast<char>(-1));
        REQUIRE_THAT(os.str(), Equals("255"s));

        os.str(""s);
        print_ip(os, static_cast<short>(0));
        REQUIRE_THAT(os.str(), Equals("0.0"s));

        os.str(""s);
        print_ip(os, static_cast<short>(-1));
        REQUIRE_THAT(os.str(), Equals("255.255"s));

        os.str(""s);
        print_ip(os, 0);
        REQUIRE_THAT(os.str(), Equals("0.0.0.0"s));

        os.str(""s);
        print_ip(os, -1);
        REQUIRE_THAT(os.str(), Equals("255.255.255.255"s));

        os.str(""s);
        print_ip(os, 0l);
        REQUIRE_THAT(os.str(), Equals("0.0.0.0.0.0.0.0"s));

        os.str(""s);
        print_ip(os, -1l);
        REQUIRE_THAT(os.str(), Equals("255.255.255.255.255.255.255.255"s));

        os.str(""s);
        print_ip(os, 0x7f000001);
        REQUIRE_THAT(os.str(), Equals("127.0.0.1"s));

        os.str(""s);
        print_ip(os, 0x1010101);
        REQUIRE_THAT(os.str(), Equals("1.1.1.1"s));
    }

    SECTION("string") {
        print_ip(os, "0.0.0.0");
        REQUIRE_THAT(os.str(), Equals("0.0.0.0"s));

        os.str(""s);
        print_ip(os, "127.0.0.1"s);
        REQUIRE_THAT(os.str(), Equals("127.0.0.1"s));
    }

    SECTION("array") {
        uint8_t zero[] = {0};
        print_ip(os, zero);
        REQUIRE_THAT(os.str(), Equals("0"));

        int ip_mask[] = {255, 255, 255, 255};
        os.str(""s);
        print_ip(os, ip_mask);
        REQUIRE_THAT(os.str(), Equals("255.255.255.255"));

        uint8_t ip_loopback[] = {127, 0, 0, 1};
        os.str(""s);
        print_ip(os, ip_loopback);
        REQUIRE_THAT(os.str(), Equals("127.0.0.1"s));
    }

    SECTION("container") {
        array<uint8_t, 1> zero = {0};
        print_ip(os, zero);
        REQUIRE_THAT(os.str(), Equals("0"));

        array<int, 4> ip_mask = {255, 255, 255, 255};
        os.str(""s);
        print_ip(os, ip_mask);
        REQUIRE_THAT(os.str(), Equals("255.255.255.255"));

        array<uint8_t, 4> ip_loopback = {127, 0, 0, 1};
        os.str(""s);
        print_ip(os, ip_loopback);
        REQUIRE_THAT(os.str(), Equals("127.0.0.1"s));
    }

    SECTION("tuple") {
        tuple<uint8_t> zero = {0};
        print_ip(os, zero);
        REQUIRE_THAT(os.str(), Equals("0"));

        auto ip_mask = make_tuple(255, 255, 255, 255);
        os.str(""s);
        print_ip(os, ip_mask);
        REQUIRE_THAT(os.str(), Equals("255.255.255.255"));

        tuple<uint8_t, uint8_t, uint8_t, uint8_t> ip_loopback = {127, 0, 0, 1};
        os.str(""s);
        print_ip(os, ip_loopback);
        REQUIRE_THAT(os.str(), Equals("127.0.0.1"s));
    }
}