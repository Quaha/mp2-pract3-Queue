#include "Queue.h"

#include <gtest.h>
#include <vector>
#include <random>

TEST(Queue, can_create_queue) {
    ASSERT_NO_THROW(Queue<int> queue);
}

TEST(Queue, default_constructor) {
    Queue<int> queue;
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(Queue, correct_push_working) {
    Queue<int> queue;

    for (int i = 0; i < 100; i++) {
        queue.push(i);
        EXPECT_EQ(queue.front(), 0);
    }
}

TEST(Queue, push_and_size) {
    Queue<int> queue;
    queue.push(5);
    queue.push(10);

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 2);
}

TEST(Queue, correct_pop_working) {
    Queue<int> queue;

    for (int i = 0; i < 100; i++) {
        queue.push(i);
    }

    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(queue.front(), i);
        queue.pop();
    }
}

TEST(Queue, pop_and_size) {
    Queue<int> queue;
    queue.push(5);
    queue.push(10);
    queue.pop();

    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 10);
}


TEST(Queue, front_on_empty_queue) {
    Queue<int> queue;
    EXPECT_ANY_THROW(queue.front());
}

TEST(Queue, pop_on_empty_queue) {
    Queue<int> queue;
    EXPECT_ANY_THROW(queue.pop());
}

TEST(Queue, copy_constructor) {
    Queue<int> queue1;
    queue1.push(1);
    queue1.push(2);

    Queue<int> queue2(queue1);

    EXPECT_EQ(queue2.size(), queue1.size());
    EXPECT_EQ(queue2.front(), queue1.front());

    queue2.pop();
    EXPECT_NE(queue2.size(), queue1.size());
    EXPECT_NE(queue2.front(), queue1.front());
}

TEST(Queue, copy_assignment_operator1) {
    Queue<int> queue1;
    queue1.push(1);
    queue1.push(2);

    Queue<int> queue2;
    queue2 = queue1;

    EXPECT_EQ(queue2.size(), queue1.size());
    EXPECT_EQ(queue2.front(), queue1.front());

    queue2.pop();
    EXPECT_NE(queue2.size(), queue1.size());
    EXPECT_NE(queue2.front(), queue1.front());
}

TEST(Queue, copy_assignment_operator2) {
    Queue<int> queue1;
    queue1.push(5);

    ASSERT_NO_THROW(queue1 = queue1);
}

TEST(Queue, move_constructor) {
    Queue<int> queue1;
    queue1.push(8);
    queue1.push(16);

    Queue<int> queue2(std::move(queue1));

    EXPECT_EQ(queue2.size(), 2);
    EXPECT_EQ(queue2.front(), 8);
    EXPECT_TRUE(queue1.empty());
}

TEST(Queue, move_assignment_operator1) {
    Queue<int> queue1;
    queue1.push(8);
    queue1.push(16);

    Queue<int> queue2;
    queue2 = std::move(queue1);

    EXPECT_EQ(queue2.size(), 2);
    EXPECT_EQ(queue2.front(), 8);
    EXPECT_TRUE(queue1.empty());
}

TEST(Queue, move_assignment_operator2) {
    Queue<int> queue1;
    queue1.push(5);

    ASSERT_NO_THROW(queue1 = std::move(queue1));
}

TEST(Queue, large_number_of_elements) {
    Queue<int> queue;
    for (int i = 0; i < 1000; ++i) {
        queue.push(i);
    }

    EXPECT_EQ(queue.size(), 1000);
    EXPECT_EQ(queue.front(), 0);
}

TEST(Queue, push_and_pop_multiple_times) {
    Queue<int> queue;
    for (int i = 0; i < 5; ++i) {
        queue.push(i);
    }
    for (int i = 0; i < 5; ++i) {
        queue.pop();
    }

    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(Queue, empty_after_push_and_pop) {
    Queue<int> queue;
    queue.push(1);
    queue.pop();

    EXPECT_TRUE(queue.empty());
}

TEST(Queue, combination_of_push_and_pop_1) {
    Queue<int> queue;

    for (int i = 0; i < 100; i++) {
        queue.push(i);
    }

    for (int i = 0; i < 100; i++) {
        queue.pop();
    }

    for (int i = 0; i < 100; i++) {
        queue.push(i);
        EXPECT_EQ(queue.front(), 0);
    }

    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(queue.front(), i);
        queue.pop();
    }
}

TEST(Queue, combination_of_push_and_pop_2) {
    Queue<int> queue;

    for (int i = 0; i < 16; i++) {
        ASSERT_NO_THROW(queue.push(i));
    }

    ASSERT_NO_THROW(queue.pop());
    for (int i = 0; i < 20; i++) {
        ASSERT_NO_THROW(queue.push(i));
    }

    while (!queue.empty()) {
        ASSERT_NO_THROW(queue.pop());
    }
}

TEST(Queue, stress_test) {
    srand(time(0));

    int COUNT_OF_TESTS = 100;
    int ACTIONS_PER_TEST = 1000;

    for (int CURR_TEST_CASE = 0; CURR_TEST_CASE < COUNT_OF_TESTS; CURR_TEST_CASE++) {
        Queue<int> queue;
        std::vector<int> queue_copy;

        for (int CURR_ACTION = 0; CURR_ACTION < ACTIONS_PER_TEST; CURR_ACTION++) {
            int type = rand() % 2;

            if (type == 0) {
                int value = rand();
                queue.push(value);
                queue_copy.push_back(value);
            }
            if (type == 1) {
                if (!queue.empty()) {
                    queue.pop();
                    queue_copy.erase(queue_copy.begin());
                }
            }

            if (!queue.empty()) {
                EXPECT_EQ(queue.front(), queue_copy[0]);
            }
            EXPECT_EQ(queue.size(), queue_copy.size());
        }
    }
}