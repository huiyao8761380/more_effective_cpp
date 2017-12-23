#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include "MockFoo.h"

using namespace seamless;
using namespace std;

using ::testing::Assign;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::Return;

int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);

  string value = "Hello World!";
  MockFoo mockFoo;
  
  EXPECT_CALL(mockFoo, setValue(testing::_));
  mockFoo.setValue(value);

  // make a mistake deliberately
  EXPECT_CALL(mockFoo, setDoubleValues(Eq(1), Ge(1)));
  mockFoo.setDoubleValues(1, 0);

  // EXPECT_CALL(mockFoo, getArbitraryString()).Times(1).WillOnce(Return(value));
  // string returnValue = mockFoo.getArbitraryString();
  // cout << "Returned Value: " << returnValue << endl;

  return EXIT_SUCCESS;
}
