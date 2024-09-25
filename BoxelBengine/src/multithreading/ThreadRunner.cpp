#include <iostream>
#include <thread>
#include <chrono>
#include <ratio>
#include <functional>

#include "ThreadRunner.h"

ThreadRunner::ThreadRunner() : state(ThreadRunnerState::WAITING), th(nullptr) {
}

ThreadRunner::~ThreadRunner() {
  delete th;
}

int default_thread(std::atomic<ThreadRunnerState>& my_state) {
  while(my_state.load() == ThreadRunnerState::RUNNING || my_state.load() == ThreadRunnerState::PAUSED) {
    while(my_state.load() == ThreadRunnerState::RUNNING) {
      std::this_thread::sleep_for(std::chrono::duration<float,std::milli>(200));
    }
    std::this_thread::sleep_for(std::chrono::duration<float,std::milli>(500));
  }
  my_state.store(ThreadRunnerState::STOPPED);
  return 0;
}


//returns int error code
int ThreadRunner::execute() {
  th = new std::thread(default_thread,std::ref(state));
  return 0;
}

ThreadRunnerState ThreadRunner::start() {
  if (state.load() != ThreadRunnerState::WAITING)
    return state.load();
  state.store(ThreadRunnerState::RUNNING);
  execute();
  return state.load();
}

ThreadRunnerState ThreadRunner::pause() {
  if (state.load() != ThreadRunnerState::RUNNING)
    return state.load();
  state.store(ThreadRunnerState::PAUSED);
  return state.load();
}

ThreadRunnerState ThreadRunner::resume() {
  if (state.load() != ThreadRunnerState::PAUSED)
    return state.load();
  state.store(ThreadRunnerState::RUNNING);
  return state.load();
}

ThreadRunnerState ThreadRunner::stop() {
  if (!(state.load() == ThreadRunnerState::RUNNING || state.load() == ThreadRunnerState::PAUSED))
    return state.load();
  state.store(ThreadRunnerState::STOPPING);
  return state.load();
}

ThreadRunnerState ThreadRunner::join() {
  th->join();
  state.store(ThreadRunnerState::STOPPED);
  return state.load();
}

ThreadRunnerState ThreadRunner::get_state() {
  return state.load();
}
