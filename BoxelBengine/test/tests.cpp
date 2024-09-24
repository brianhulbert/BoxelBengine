#include <gtest/gtest.h>

#include "multithreading/ThreadRunner.h"

TEST(MultithreadingTest, ThreadStart) {
  ThreadRunner th;

  EXPECT_EQ(th.get_state(),ThreadRunnerState::WAITING);

  th.start();

  EXPECT_EQ(th.get_state(),ThreadRunnerState::RUNNING);

  th.pause();

  EXPECT_EQ(th.get_state(),ThreadRunnerState::PAUSED);

  th.resume();
  
  EXPECT_EQ(th.get_state(),ThreadRunnerState::RUNNING);

  th.stop();

  EXPECT_EQ(th.get_state(),ThreadRunnerState::STOPPING);

}
