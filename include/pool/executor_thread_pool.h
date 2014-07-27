#ifndef POOL_EXECUTOR_THREAD_POOL_H
#define POOL_EXECUTOR_THREAD_POOL_H

#include <vector>
#include <functional>
#include <thread>
#include <config/config.h>
#include <instrumentation/instrumentation.h>
#include <tbb/concurrent_queue.h>

typedef std::function<void()> task_fn_t;

class executor_thread_pool {
public:
  executor_thread_pool(instrumentation & instr, const config & conf);
  void add_task(const task_fn_t & task);
  void stop();

private:
  void run_tasks(const int i);

private:
  typedef struct {
    task_fn_t fn;
    bool stop;
  } task_t;

  instrumentation & instr_;
  instrumentation::id_t gauge_id_;
  std::vector<int> finished_threads_;
  std::vector<std::thread> threads_;
  tbb::concurrent_bounded_queue<task_t> tasks_;

};

#endif
