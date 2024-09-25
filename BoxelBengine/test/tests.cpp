#include <gtest/gtest.h>

#include <thread>
#include <chrono>
#include <ratio>

#include "multithreading/ThreadRunner.h"

TEST(MultithreadingTest, ThreadStateTransitions) {
  ThreadRunner* th = new ThreadRunner();
  
  std::cout << "State: " << static_cast<std::underlying_type<ThreadRunnerState>::type>(th->get_state()) << std::endl;
  EXPECT_EQ(th->get_state(),ThreadRunnerState::WAITING);

  th->start();

  std::cout << "State: " << static_cast<std::underlying_type<ThreadRunnerState>::type>(th->get_state()) << std::endl;
  EXPECT_EQ(th->get_state(),ThreadRunnerState::RUNNING);

  th->pause();

  std::cout << "State: " << static_cast<std::underlying_type<ThreadRunnerState>::type>(th->get_state()) << std::endl;
  EXPECT_EQ(th->get_state(),ThreadRunnerState::PAUSED);

  th->resume();
  
  std::cout << "State: " << static_cast<std::underlying_type<ThreadRunnerState>::type>(th->get_state()) << std::endl;
  EXPECT_EQ(th->get_state(),ThreadRunnerState::RUNNING);

  th->stop();

  std::cout << "State: " << static_cast<std::underlying_type<ThreadRunnerState>::type>(th->get_state()) << std::endl;
  EXPECT_EQ(th->get_state(),ThreadRunnerState::STOPPING);

  th->join();
  
  std::cout << "State: " << static_cast<std::underlying_type<ThreadRunnerState>::type>(th->get_state()) << std::endl;
  EXPECT_EQ(th->get_state(),ThreadRunnerState::STOPPED);

  delete th;
}
