/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

//
// This contains SlowWorker, which runs (expensive) tasks in a background thread
// when it's not otherwise busy.

#ifndef PAGESPEED_KERNEL_THREAD_SLOW_WORKER_H_
#define PAGESPEED_KERNEL_THREAD_SLOW_WORKER_H_

#include "pagespeed/kernel/base/basictypes.h"
#include "pagespeed/kernel/base/string_util.h"
#include "pagespeed/kernel/thread/worker.h"

namespace net_instaweb {

class Function;
class ThreadSystem;

// See file comment.
class SlowWorker : public Worker {
 public:
  // Initializes the worker. You still need to call ->Start to actually
  // start the thread, however. (Note: start can return false on failure).
  SlowWorker(StringPiece thread_name, ThreadSystem* runtime);

  // This waits for the running task to terminate.
  ~SlowWorker() override;

  // If this SlowWorker's thread is currently idle, it will run the closure.
  // Otherwise, the closure will simply be deleted.
  //
  // Takes ownership of the closure.
  void RunIfNotBusy(Function* closure);

 private:
  bool IsPermitted(Function* closure) override;

  DISALLOW_COPY_AND_ASSIGN(SlowWorker);
};

}  // namespace net_instaweb

#endif  // PAGESPEED_KERNEL_THREAD_SLOW_WORKER_H_
