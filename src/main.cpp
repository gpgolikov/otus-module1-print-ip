#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <array>

#include "print_ip.h"

using namespace std;
using namespace griha;

int main() {
    print_ip(cout, static_cast<char>(-1));
    endl(cout);
    print_ip(cout, static_cast<short>(0));
    endl(cout);
    print_ip(cout, 2130706433);
    endl(cout);
    print_ip(cout, 8875824491850138409l);
    endl(cout);
    print_ip(cout, "192.168.8.1");
    endl(cout);
    print_ip(cout, vector<int> {10, 20, 77, 15});
    endl(cout);
    print_ip(cout, list<int> {0, 0, 0, 0});
    endl(cout);
    print_ip(cout, make_tuple(100, 100, 100, 100));
    endl(cout);
    print_ip(cout, array<const char*, 4>{ "127", "0", "0", "1" });
    endl(cout);

    return 0;
}