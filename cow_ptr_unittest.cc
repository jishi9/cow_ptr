#include "cow_ptr.h"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class Foo.
class CowPtrTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  CowPtrTest() {
    // You can do set-up work for each test here.
  }

  virtual ~CowPtrTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(CowPtrTest, NewCopyDoesNotAffectOld) {
  cow_ptr<int> copy1(new int(13));
  *copy1 = 10;
  EXPECT_EQ(10, *copy1);

  cow_ptr<int> copy2(copy1);
  *copy1 = 20;
  *copy2 = 30;
  EXPECT_EQ(20, *copy1);
  EXPECT_EQ(30, *copy2);
}

// Tests that the Foo::Bar() method does Abc.
TEST_F(CowPtrTest, NonOwningConstructorDoesNotDestroyOriginal) {
  struct DeleteCounter  {
    int* counter_;
    DeleteCounter(int* counter) : counter_(counter) {}
    ~DeleteCounter() {
      (*counter_)++;
    }
    void read() const {}
    void touch() {}
  };

  int delete_counter = 0;
  DeleteCounter d(&delete_counter);

  {
    cow_ptr<DeleteCounter> ref_to_original(&d, false);
  }
  ASSERT_EQ(0, delete_counter);

  {
    cow_ptr<DeleteCounter> ref_to_original(&d, false);

    {
      const cow_ptr<DeleteCounter> copy_of_original(ref_to_original);
      copy_of_original->read();
    }
    // No copy is made
    ASSERT_EQ(0, delete_counter);

    {
      cow_ptr<DeleteCounter> copy_of_original(ref_to_original);
      copy_of_original->read();
    }
    // No copy is made
    ASSERT_EQ(0, delete_counter);

    {
      cow_ptr<DeleteCounter> copy_of_original(ref_to_original);
      copy_of_original->touch();
    }
    // A copy is made
    ASSERT_EQ(1, delete_counter);
  }
  ASSERT_EQ(1, delete_counter);
}

// Tests that the Foo::Bar() method does Abc.
TEST_F(CowPtrTest, NonOwningConstructorDoesNotDestroyOriginalaa) {

}  // namespace

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
