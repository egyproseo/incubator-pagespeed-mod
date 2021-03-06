load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load(
    "//bazel:pagespeed_test.bzl",
    "pagespeed_cc_test",
    "pagespeed_cc_test_library",
)

licenses(["notice"])  # Apache 2

proto_library(
    name = "controller_proto",
    srcs = ["controller.proto"],
)

cc_proto_library(
    name = "controller_proto_cc",
    deps = [":controller_proto"],
)

cc_grpc_library(
    name = "controller_proto_grpc",
    srcs = [
        ":controller_proto",
    ],
    grpc_only = True,
    proto_only = False,
    use_external = False,
    visibility = ["//visibility:public"],
    well_known_protos = True,
    deps = [
        ":controller_proto_cc",
    ],
)

cc_library(
    name = "controller",
    srcs = [
        "central_controller.cc",
        "central_controller_rpc_client.cc",
        "central_controller_rpc_server.cc",
        "compatible_central_controller.cc",
        "expensive_operation_callback.cc",
        "expensive_operation_rpc_context.cc",
        "expensive_operation_rpc_handler.cc",
        "in_process_central_controller.cc",
        "named_lock_schedule_rewrite_controller.cc",
        "popularity_contest_schedule_rewrite_controller.cc",
        "queued_expensive_operation_controller.cc",
        "schedule_rewrite_callback.cc",
        "schedule_rewrite_rpc_context.cc",
        "schedule_rewrite_rpc_handler.cc",
        "work_bound_expensive_operation_controller.cc",
    ],
    hdrs = [
        "central_controller.h",
        "central_controller_callback.h",
        "central_controller_rpc_client.h",
        "central_controller_rpc_server.h",
        "compatible_central_controller.h",
        "context_registry.h",
        "expensive_operation_callback.h",
        "expensive_operation_controller.h",
        "expensive_operation_rpc_context.h",
        "expensive_operation_rpc_handler.h",
        "in_process_central_controller.h",
        "named_lock_schedule_rewrite_controller.h",
        "popularity_contest_schedule_rewrite_controller.h",
        "priority_queue.h",
        "queued_expensive_operation_controller.h",
        "request_result_rpc_client.h",
        "request_result_rpc_handler.h",
        "rpc_handler.h",
        "schedule_rewrite_callback.h",
        "schedule_rewrite_controller.h",
        "schedule_rewrite_rpc_context.h",
        "schedule_rewrite_rpc_handler.h",
        "work_bound_expensive_operation_controller.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":controller_proto_grpc",
        "//pagespeed/kernel/base:pagespeed_base",
        "//pagespeed/kernel/thread",
        "//pagespeed/kernel/util",
        "//pagespeed/system:system_controller_process_h",
        "//third_party/rdestl",
    ],
)

pagespeed_cc_test_library(
    name = "controller_test_base",
    srcs = [
        "grpc_server_test.cc",
    ],
    hdrs = [
        "controller_grpc_mocks.h",
        "grpc_server_test.h",
    ],
    deps = [
        ":controller",
        "//pagespeed/kernel/base:pagespeed_gtest",
        "//pagespeed/kernel/thread:thread_test_base",
        "//pagespeed/kernel/util",
    ],
)

proto_library(
    name = "grpc_test_proto",
    srcs = ["grpc_test.proto"],
)

cc_proto_library(
    name = "grpc_test_proto_cc",
    deps = [":grpc_test_proto"],
)

cc_grpc_library(
    name = "grpc_test_proto_grpc",
    srcs = [
        ":grpc_test_proto",
    ],
    grpc_only = True,
    proto_only = False,
    use_external = False,
    visibility = ["//visibility:public"],
    well_known_protos = True,
    deps = [
        ":grpc_test_proto_cc",
    ],
)

pagespeed_cc_test(
    name = "controller_test",
    srcs = [
        "central_controller_callback_test.cc",
        "context_registry_test.cc",
        "expensive_operation_rpc_context_test.cc",
        "expensive_operation_rpc_handler_test.cc",
        "named_lock_schedule_rewrite_controller_test.cc",
        "popularity_contest_schedule_rewrite_controller_test.cc",
        "priority_queue_test.cc",
        "queued_expensive_operation_controller_test.cc",
        "rpc_handler_test.cc",
        "schedule_rewrite_rpc_context_test.cc",
        "schedule_rewrite_rpc_handler_test.cc",
        "work_bound_expensive_operation_controller_test.cc",
    ],
    deps = [
        ":controller_test_base",
        ":grpc_test_proto_grpc",
        "//pagespeed/kernel/base:pagespeed_base",
    ],
)
