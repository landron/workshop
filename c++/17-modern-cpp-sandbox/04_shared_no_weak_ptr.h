#pragma once

#include <gtest/gtest.h>
#include <memory>

// This test demonstrates the danger of using std::shared_ptr for both
// "next" and "prev" pointers in a doubly linked list.
// The resulting cycle keeps the nodes alive even after the external
// owning shared_ptrs are released.
struct DoubleLinkedNode final {
    int value;
    std::shared_ptr<DoubleLinkedNode> next;
    std::shared_ptr<DoubleLinkedNode> prev;

    inline static int destructor_count = 0;

    explicit DoubleLinkedNode(int value) noexcept : value(value) {}

    ~DoubleLinkedNode() noexcept {
        ++destructor_count;
    }
};

TEST(SharedPtrNoWeakPtrTest, CircularSharedPtrDoubleLinkedListKeepsNodesAlive) {
    DoubleLinkedNode::destructor_count = 0;

    auto a = std::make_shared<DoubleLinkedNode>(1);
    auto b = std::make_shared<DoubleLinkedNode>(2);
    ASSERT_EQ(a.use_count(), 1u);

    a->next = b;
    b->prev = a;

    EXPECT_EQ(a.use_count(), 2u);
    EXPECT_EQ(b.use_count(), 2u);

    // CTAD (Compile-Time Argument Deduction) available since C++17
    std::weak_ptr weak_a = a;
    std::weak_ptr weak_b = b;

    a.reset();
    b.reset();

    EXPECT_EQ(DoubleLinkedNode::destructor_count, 0)
        << "Nodes should not be destroyed due to circular shared_ptr "
           "references";
    EXPECT_FALSE(weak_a.expired())
        << "Weak pointer not expired since node is still alive after reset()";
    EXPECT_FALSE(weak_b.expired());

    auto locked_a = weak_a.lock();
    auto locked_b = weak_b.lock();

    ASSERT_TRUE(locked_a);
    ASSERT_TRUE(locked_b);
    EXPECT_EQ(locked_a.use_count(), 2u);
    EXPECT_EQ(locked_b.use_count(), 2u);
}

struct DoubleLinkedNodeWithWeakPrev final {
    int value;
    std::shared_ptr<DoubleLinkedNodeWithWeakPrev> next;
    std::weak_ptr<DoubleLinkedNodeWithWeakPrev> prev;

    // In a production environment, you'd use AddressSanitizer (ASan)
    // to catch these leaks automatically without the extra code.
    inline static int destructor_count = 0;

    explicit DoubleLinkedNodeWithWeakPrev(int value) noexcept : value(value) {}

    ~DoubleLinkedNodeWithWeakPrev() noexcept {
        ++destructor_count;
    }
};

TEST(SharedPtrWithWeakPtrTest, DoublyLinkedListBreaksCycleWithWeakPrev) {
    DoubleLinkedNodeWithWeakPrev::destructor_count = 0;

    auto a = std::make_shared<DoubleLinkedNodeWithWeakPrev>(1);
    auto b = std::make_shared<DoubleLinkedNodeWithWeakPrev>(2);

    a->next = b;
    b->prev = a;

    ASSERT_EQ(a.use_count(), 1u);
    ASSERT_EQ(b.use_count(), 2u);

    std::weak_ptr weak_a = a;
    std::weak_ptr weak_b = b;

    a.reset();
    ASSERT_TRUE(weak_a.expired()) << "Weak prev does not keep node alive after "
                                     "owning shared_ptr is released";
    EXPECT_EQ(DoubleLinkedNodeWithWeakPrev::destructor_count, 1);

    b.reset();
    ASSERT_TRUE(weak_b.expired());
    EXPECT_EQ(DoubleLinkedNodeWithWeakPrev::destructor_count, 2u);
}
