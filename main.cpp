#include<iostream>
#include <cassert>
#include <functional>
#include "optional.h"

void test_defaultConstructor() {
    optional<int> a(3);
    assert(a && *a == 3);
}

void test_copyConstructor() {
    optional<int> a(3);
    optional<int> b(a);
    assert(b && *b == 3);
}

void test_not_explicit() {
    optional<int> f;
    assert(!f);
    f = 3;
    assert(f);
}

void test_swap() {
    optional<int> a(3);
    optional<int> b;
    swap(a, b);
    assert(!a && b && *b == 3);
}

void tg_test() {
    optional<int> a, b;
    b = 3;
    a = b;
    (*a)++;
    assert(a && b && *a == 4 && *b == 3);
}

void clear_test() {
    optional<int> b;
    b = 2;
    assert(b);
    b.clear();
    assert(!b);
}

void test_struct() {
    optional<std::pair<int, bool>> opt;
    assert(!opt);
    opt = std::make_pair(3, false);
    assert(opt && opt->first == 3 && !opt->second);
    opt->second = bool(opt);
    assert(opt && opt->first == 3 && opt->second);
}

void test_link() {
    std::vector<int> a = {1, 2, 3};
    optional<std::vector<int> *> st(&a);
    assert(st && (**st)[1] == 2);
}

void all_test() {
    test_defaultConstructor();
    test_copyConstructor();
    test_not_explicit();
    test_swap();
    tg_test();
    clear_test();
    test_struct();
    test_link();
    std::cout << "OK!";
}

int main() {
    all_test();
    return 0;
}