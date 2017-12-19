#include <array>
#include <stack>
#include <string>
#include <utility>

#include <gtest/gtest.h>

#include "alg/common/exception.h"
#include "alg/common/randomizer.h"
#include "alg/data_structure/stack.h"
#include "tests/helper.h"

namespace algtest {

TEST(Stack, Empty) {
    alg::Stack<int> s(2);

    ASSERT_THROW(s.pop(), alg::except::BufferEmpty);
}

TEST(Stack, Full) {
    alg::Stack<int> s(2);

    ASSERT_NO_THROW(s.push(2));
    ASSERT_NO_THROW(s.push(3));
    ASSERT_THROW(s.push(5), alg::except::BufferFull);
}

TEST(Stack, PushPop) {
    constexpr int n = 10;
    std::array<int, n> data = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    alg::Stack<int> s(n);

    for (int i = 0; i < n; i++) {
        s.push(data[i]);
    }

    for (int i = 0; i < n; i++) {
        ASSERT_EQ(data[n - 1 - i], s.pop());
    }
}

TEST(Stack, Top) {
    alg::Stack<int> s(2);

    ASSERT_THROW(s.top(), alg::except::BufferEmpty);

    s.push(2);

    ASSERT_EQ(2, s.top());
    ASSERT_EQ(2, s.top());
}

TEST(Stack, Count) {
    int n = 17;
    int d1 = 13;
    int d2 = 7;
    alg::Stack<int> s(n);

    ASSERT_EQ(0, s.count());

    for (int i = 0; i < n; i++) {
        s.push(i);
    }

    ASSERT_EQ(n, s.count());

    for (int i = 0; i < d1; i++) {
        s.pop();
    }

    ASSERT_EQ(n - d1, s.count());

    for (int i = 0; i < d2; i++) {
        s.push(i);
    }

    ASSERT_EQ(n - d1 + d2, s.count());

    for (int i = 0; i < n - d1 + d2; i++) {
        s.pop();
    }

    ASSERT_EQ(0, s.count());
}

TEST(Stack, CopyConstructor) {
    std::array<std::string, 8> data = {"a", "b", "c", "d", "e", "f", "g", "h"};
    alg::Stack<std::string> st(data.size());

    for (std::size_t i = 0; i < data.size() / 2; i++) {
        st.push(data[i]);
    }

    alg::Stack<std::string> st_copied = st;

    for (std::size_t i = data.size() / 2; i < data.size(); i++) {
        st.push(data[i]);
    }

    st_copied.push("foo");

    ASSERT_EQ(data.size(), st.count());
    ASSERT_EQ(data.size() / 2 + 1, st_copied.count());

    ASSERT_EQ("foo", st_copied.pop());

    for (int i = data.size() - 1; i >= 0; i--) {
        ASSERT_EQ(data[i], st.pop());
    }

    for (int i = data.size() / 2 - 1; i >= 0; i--) {
        ASSERT_EQ(data[i], st_copied.pop());
    }

    ASSERT_EQ(0, st.count());
    ASSERT_EQ(0, st_copied.count());
}

TEST(Stack, MoveConstructor) {
    std::array<std::string, 8> data = {"a", "b", "c", "d", "e", "f", "g", "h"};
    alg::Stack<std::string> st(data.size());

    for (std::size_t i = 0; i < data.size() / 2; i++) {
        st.push(data[i]);
    }

    alg::Stack<std::string> st_moved = std::move(st);

    for (std::size_t i = data.size() / 2; i < data.size(); i++) {
        st_moved.push(data[i]);
    }

    ASSERT_EQ(data.size(), st_moved.count());
    ASSERT_EQ(0, st.count());

    for (int i = data.size() - 1; i >= 0; i--) {
        ASSERT_EQ(data[i], st_moved.pop());
    }

    st.push("foo");

    ASSERT_EQ("foo", st.top());
    ASSERT_EQ(1, st.count());
    ASSERT_EQ("foo", st.pop());
}

TEST(Stack, SelfCopyAssignment) {
    std::array<std::string, 8> data = {"a", "b", "c", "d", "e", "f", "g", "h"};
    alg::Stack<std::string> st(data.size() * 2);

    for (std::size_t i = 0; i < data.size(); i++) {
        st.push(data[i]);
    }

    st = st;

    for (int i = data.size() - 1; i >= 0; i--) {
        ASSERT_EQ(data[i], st.pop());
    }

    st.push("foo");

    ASSERT_EQ(1, st.count());
}

template <class T, std::size_t NL, std::size_t NR>
void assert_stack_copy_assignment(const std::array<T,NL>& lhs_data,
        const std::array<T,NR>& rhs_data) {

    alg::Stack<T> lhs_st(lhs_data.size() * 2);
    alg::Stack<T> rhs_st(rhs_data.size() * 2);

    for (std::size_t i = 0; i < lhs_data.size(); i++) {
        lhs_st.push(lhs_data[i]);
    }

    for (std::size_t i = 0; i < rhs_data.size(); i++) {
        rhs_st.push(rhs_data[i]);
    }

    ASSERT_EQ(lhs_data.size(), lhs_st.count());
    ASSERT_EQ(rhs_data.size(), rhs_st.count());

    lhs_st = rhs_st;

    ASSERT_EQ(rhs_st.count(), lhs_st.count());

    while (rhs_st.count()) {
        ASSERT_EQ(rhs_st.pop(), lhs_st.pop());
    }
}

TEST(Stack, CopyAssignmentDifferentSize) {
    std::array<std::string, 4> lhs_data = {"a", "b", "c", "d"};
    std::array<std::string, 6> rhs_data = {"x", "y", "z", "p", "q", "r"};

    assert_stack_copy_assignment(lhs_data, rhs_data);
}

TEST(Stack, CopyAssignmentSameSize) {
    std::array<std::string, 6> lhs_data = {"a", "b", "c", "d", "e", "f"};
    std::array<std::string, 6> rhs_data = {"x", "y", "z", "p", "q", "r"};

    assert_stack_copy_assignment(lhs_data, rhs_data);
}

TEST(Stack, LargeRandomDataSet) {
    constexpr int total = 100000;
    constexpr int delete_freq = 10;

    std::stack<NoDefaultCtor<int>> std_stack;
    alg::Stack<NoDefaultCtor<int>> alg_stack(total);

    for (int i = 0; i < total; i++) {
        int data = alg::randomizer::uniform_int(-total, total);

        NoDefaultCtor<int> std_data(data);
        NoDefaultCtor<int> alg_data(data);

        std_stack.push(std_data);
        alg_stack.push(alg_data);

        if (!(i % delete_freq)) {
            ASSERT_EQ(std_stack.top().data(), alg_stack.top().data());

            std_stack.pop();
            alg_stack.pop();
        }
    }

    ASSERT_EQ(std_stack.size(), alg_stack.count());

    while (std_stack.size()) {
        ASSERT_EQ(std_stack.top().data(), alg_stack.pop().data());

        std_stack.pop();
    }

    ASSERT_EQ(0, alg_stack.count());
}

}
