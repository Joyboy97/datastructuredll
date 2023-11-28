cmake_minimum_required(VERSION 3.26)
project(TaskManager)

set(CMAKE_CXX_STANDARD 14)

include_directories("Task Manager/DLLTaskManager")

add_executable(TaskManager
        "Task Manager/.metadata/.plugins/org.eclipse.cdt.make.core/specs.c"
        "Task Manager/.metadata/.plugins/org.eclipse.cdt.make.core/specs.cpp"
        "Task Manager/.metadata/.plugins/org.eclipse.cdt.managedbuilder.core/spec.c"
        "Task Manager/.metadata/.plugins/org.eclipse.cdt.managedbuilder.core/spec.cpp"
        "Task Manager/DLLTaskManager/DLL.cpp"
        "Task Manager/DLLTaskManager/DLL.hpp"
        "Task Manager/DLLTaskManager/DNode.cpp"
        "Task Manager/DLLTaskManager/DNode.hpp"
        "Task Manager/DLLTaskManager/MainDLL.cpp"
        "Task Manager/DLLTaskManager/Task.cpp"
        "Task Manager/DLLTaskManager/Task.hpp"
        "Task Manager/DLLTaskManager/TaskManager.cpp"
        "Task Manager/DLLTaskManager/TaskManager.hpp")
