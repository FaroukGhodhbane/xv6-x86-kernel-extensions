#include "types.h"
#include "stat.h"
#include "user.h"

// Case 0 runs all tests
void test_invalid_pids(void) {}  // case 1
void test_init(void) {}  // case 2
void test_self(void) {}  // case 3
void test_child_parent(void) {}  // case 4
void test_siblings(void) {}  // case 5
void test_grandchild_grandparent(void) {}  // case 6

// Helper function for printing
void assert_distance(
  int pid1,
  int pid2,
  int expected_distance,
  const char* msg
){
  int actual_distance = getLCADistance(pid1, pid2);
  if(actual_distance == expected_distance){
    printf(1, "[PASS] %s | getLCADistance(%d, %d) == %d\n", msg, pid1, pid2, actual_distance);
  } else{
    printf(1, "[FAIL] %s| getLCADistance(%d, %d) expected %d, got %d\n", msg, pid1, pid2, expected_distance, actual_distance);
  }
}

int main(int argc, char* argv[]){
  int test_num = 0;  // Default: runs all tests sequentially (1-6)

  if(argc > 1){
    test_num = atoi(argv[1]);
  }

  printf(1, "--- Running getLCADistance Test Suite ---\n");

  switch(test_num){
    case 1:
      test_invalid_pids();
      break;

    case 2:
      test_init();
      break;

    case 3:
      test_self();
      break;

    case 4:
      test_child_parent();
      break;

    case 5:
      test_siblings();
      break;

    case 6:
      test_grandchild_grandparent();
      break;

    case 0:
    default:
      test_invalid_pids();
      test_init();
      test_self();
      test_child_parent();
      test_siblings();
      test_grandchild_grandparent();
      break;
  }

  printf(1, "--- Test Suite Completed ---\n");
  exit();
}