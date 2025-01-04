cmake_minimum_required(VERSION 3.5.0)

project(PTAHomework VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设定包含目录
find_package(OpenCV REQUIRED)
include_directories(src_PTA/5-String/lib)
include_directories(src_PTA/4-Queue/lib)
# include_directories(${OpenCV_INCLUDE_DIRS})

# 生成库
add_library(libString SHARED src_PTA/4-Queue/lib/Queue.cpp)

# temp 测试用


add_executable(temp temp.cpp
        src_PTA/5-String/lib/String.cpp)
target_link_libraries(temp libString)
# target_link_libraries(temp ${OpenCV_LIBRARIES})

#message(STATUS "OpenCV version: ${OpenCV_VERSION}")
#message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
#message(STATUS "OpenCV libraries: ${OpenCV_LIBRARIES}")

# 第三部分
#add_executable(3-7-2 src_PTA/3-Stack/3-7-2_SymbolPairing.cpp)
#add_executable(3-7-3 src_PTA/3-Stack/3-7-3_NifixExpressionCalculation.cpp)
#add_executable(3-7-4 src_PTA/3-Stack/3-7-4_NifixExpressionConvertion.cpp)
#add_executable(3-7-5 src_PTA/3-Stack/3-7-5_Palindrome.cpp)
#add_executable(3-7-6 src_PTA/3-Stack/3-7-6_StackOperationValidity.cpp)
#add_executable(3-7-7 src_PTA/3-Stack/3-7-7_SimpleCalculator.cpp)

# 第四部分
#add_executable(4-7-1 src_PTA/4-Queue/4-7-1_SuperStairs.cpp)
#add_executable(4-7-2 src_PTA/4-Queue/4-7-2_RecursiveReverseOutput.cpp)
#add_executable(4-7-3 src_PTA/4-Queue/4-7-3_HanoiProblem.cpp)
#add_executable(4-7-4 src_PTA/4-Queue/4-7-4_LinkLiskMultiplies.cpp)
#add_executable(4-7-5 src_PTA/4-Queue/4-7-5_JosephProblem.cpp)

# 第五部分
# add_executable(5-6-1 src_PTA/5-String/5-6-1_KMP.cpp)

# 第六部分
# add_executable(6-7-1 src_PTA/6-Arrays&GeneralizedList/6-7-1_TripleTranspose.cpp)
# add_executable(6-7-2 src_PTA/6-Arrays&GeneralizedList/6-7-2_TripleAdd.cpp)
add_executable(7-6-1 src_PTA/7-BinaryTree/7-6-1_IterateInOrderSearchBinaryTree.cpp)
add_executable(7-6-2 src_PTA/7-BinaryTree/7-7-1_TreeNodeReverse.cpp)
add_executable(4-7-3 src_PTA/4-Queue/4-7-3_HanoiProblem.cpp)
