#include "types.h"
#include "stat.h"
#include "user.h"

// Case 0 runs all tests
void test_invalid_pids(void);  // case 1
void test_init(void); // case 2
void test_self(void);  // case 3
void test_child_parent(void);  // case 4
void test_siblings(void);  // case 5
void test_grandchild_grandparent(void);  // case 6

// Helper function for printing results
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

// case 1
void test_invalid_pids(void){
  int test_pid = getpid();
  assert_distance(100, test_pid, -2, "Invalid pid1");
  assert_distance(test_pid, 100, -2, "Invalid pid 2");
}
 
// case 2
void test_init(void){  // case 2
  int test_pid = getpid();
  assert_distance(test_pid, 1, -1, "Boundary Check Against init (PID = 1)");
  assert_distance(1, test_pid, -1, "Boundary Check Against init (PID = 1)");
}

// case 3
void test_self(void){
  int test_pid = getpid();
  assert_distance(test_pid, test_pid, 0, "Same Process Check");
}

// case 4
void test_child_parent(void){
  int parent_process_pid = getpid();
  int child_process_pid = fork();
  if(child_process_pid == 0){
    sleep(100);  // Let child sleep long enough for the assertion
    exit();
  }

  assert_distance(parent_process_pid, child_process_pid, 1, "Parent to Child Check");
  assert_distance(child_process_pid, parent_process_pid, 1, "Child to Parent Check");

  kill(child_process_pid);  // Terminate child process
  wait();  // Clean process table
}

// case 5
void test_siblings(void){
  int child_process_1_pid = fork();
  if(child_process_1_pid == 0){
    sleep(100);
    exit();
  }

  int child_process_2_pid = fork();
  if(child_process_2_pid == 0){
    sleep(100);
    exit();
  }

  assert_distance(child_process_1_pid, child_process_2_pid, 2, "Siblings One Direction Check");
  assert_distance(child_process_2_pid, child_process_1_pid, 2, "Siblings Other Direction Check");

  kill(child_process_1_pid);
  kill(child_process_2_pid);
  wait();
  wait();
}

// case 6
void test_grandchild_grandparent(void){
  int grandparent_process_pid = getpid();
  int child_process_pid = fork();

  if(child_process_pid == 0){
    int grandchild_process_pid = fork();

    if(grandchild_process_pid == 0){
      sleep(100);
      exit();
    }

    assert_distance(grandparent_process_pid, grandchild_process_pid, 2, "Grandparent to Grandchild Check");
    assert_distance(grandchild_process_pid, grandparent_process_pid, 2, "Grandchild to Grandparent Check");

    kill(grandchild_process_pid);
    wait();
    exit();
  }
  wait();
}