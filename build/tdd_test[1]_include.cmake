if(EXISTS "/home/polina/Desktop/2semestr/IVS/PROJEKT1/build/tdd_test[1]_tests.cmake")
  include("/home/polina/Desktop/2semestr/IVS/PROJEKT1/build/tdd_test[1]_tests.cmake")
else()
  add_test(tdd_test_NOT_BUILT tdd_test_NOT_BUILT)
endif()