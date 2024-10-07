
// Includes for code to be tested
#include "da6.hpp"           // For Assignment 6 templates
#include "da6.hpp"           // Double inclusion check, for testing only

// Includes for all test programs
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;

// Additional includes for this test program
#include "llnode2.hpp"       // For LLNode2
#include <cstddef>
using std::size_t;
#include <stdexcept>
using std::runtime_error;
#include <string>
using std::string;
#include <memory>
using std::unique_ptr;
#include <sstream>
using std::ostringstream;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
#include <utility>
using std::pair;
using std::make_pair;
#include <ostream>
using std::ostream;
#include <stdexcept>
using std::out_of_range;

int main () {

    SlowMap<int, string> m;
    m.set(100, "abc");
    const SlowMap<int, string> & cm(m);

    if (!m.empty()) cout << "Is not empty\n";
    if (m.size() == 1) cout << "Size is 1\n";
    if (m.present(1) == false) cout << "Key '1' on size-1 SlowMap returns nullptr\n";
    if (m.present(100) == true) cout << "Key '100' on size-1 SlowMap returns true\n";
    try {
        m.get(1);
    } catch (out_of_range & e) {
        if(e.what() != "") cout << "'what' member of exception is not empty\n";
    }
    auto v = m.get(100);
    cout << "v = " << v << ": is should equal abc\n";
    try {
        cm.get(1);
    }
    catch (out_of_range & e) {
        if(e.what() != "") cout << "'what' member of exception is not empty\n";
    }
    auto g = cm.get(100);
    cout << "g = " << g << ": is should equal abc\n";

    return 0;
}