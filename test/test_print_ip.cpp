#include <catch2/catch.hpp>

#include <sstream>
#include <array>
#include <tuple>
#include <string>
#include <string_view>

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
        REQUIRE_THAT(os.str(), Equals("0"s));

        int ip_mask[] = {255, 255, 255, 255};
        os.str(""s);
        print_ip(os, ip_mask);
        REQUIRE_THAT(os.str(), Equals("255.255.255.255"s));

        uint8_t ip_loopback[] = {127, 0, 0, 1};
        os.str(""s);
        print_ip(os, ip_loopback);
        REQUIRE_THAT(os.str(), Equals("127.0.0.1"s));
    }

    SECTION("container") {
        array<uint8_t, 1> zero = {0};
        print_ip(os, zero);
        REQUIRE_THAT(os.str(), Equals("0"s));

        array<int, 4> ip_mask = {255, 255, 255, 255};
        os.str(""s);
        print_ip(os, ip_mask);
        REQUIRE_THAT(os.str(), Equals("255.255.255.255"s));

        array<uint8_t, 4> ip_loopback = {127, 0, 0, 1};
        os.str(""s);
        print_ip(os, ip_loopback);
        REQUIRE_THAT(os.str(), Equals("127.0.0.1"s));
    }

    SECTION("tuple") {
        tuple<uint8_t> zero = {0};
        print_ip(os, zero);
        REQUIRE_THAT(os.str(), Equals("0"s));

        auto ip_mask = make_tuple(255, 255, 255, 255);
        os.str(""s);
        print_ip(os, ip_mask);
        REQUIRE_THAT(os.str(), Equals("255.255.255.255"s));

        tuple<uint8_t, uint8_t, uint8_t, uint8_t> ip_loopback = {127, 0, 0, 1};
        os.str(""s);
        print_ip(os, ip_loopback);
        REQUIRE_THAT(os.str(), Equals("127.0.0.1"s));
    }

    SECTION("initializer_list") {
        print_ip(os, { 0 });
        REQUIRE_THAT(os.str(), Equals("0"s));

        os.str(""s);
        print_ip(os, { 255, 255, 255, 255 });
        REQUIRE_THAT(os.str(), Equals("255.255.255.255"s));

        os.str(""s);
        print_ip(os, { 127, 0, 0, 1 });
        REQUIRE_THAT(os.str(), Equals("127.0.0.1"s));
    }

    SECTION("non-integral types") {
        print_ip(os, make_tuple("127", "0", "0", "1"));
        REQUIRE_THAT(os.str(), Equals("127.0.0.1"s));

        os.str(""s);
        print_ip(os, array<string, 4> {"255"s, "255"s, "255"s, "255"s});
        REQUIRE_THAT(os.str(), Equals("255.255.255.255"s));

        os.str(""s);
        string_view ip[] = {"0"sv, "0"sv, "0"sv, "0"sv};
        print_ip(os, ip);
        REQUIRE_THAT(os.str(), Equals("0.0.0.0"s));

        os.str(""s);
        print_ip(os, {"1", "1", "1", "1"});
        REQUIRE_THAT(os.str(), Equals("1.1.1.1"s));
    }
}