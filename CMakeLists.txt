cmake_minimum_required(VERSION 4.0)
project(behaviortree_to_maya_test CXX)

add_subdirectory(action)


SET(MAYA_PLUGIN_NAME "behaviortree_to_maya_test")
SET(MAYA_DIRECTORY "C:/Program Files/Autodesk/Maya2022")
SET(MAYA_HEADERS_DIR "${MAYA_DIRECTORY}/include")
SET(MAYA_LIBRARY_DIR "${MAYA_DIRECTORY}/lib")

SET(SOURCE_FILES
        src/plugin.cpp
        src/plugin.h
        action/src/TestAction.cpp
        action/include/TestAction.h
)

source_group("" FILES ${SOURCE_FILES})

INCLUDE_DIRECTORIES(${MAYA_HEADERS_DIR})
INCLUDE_DIRECTORIES("${MAYA_HEADERS_DIR}/Qt")
LINK_DIRECTORIES(${MAYA_LIBRARY_DIR})

SET(LIBRARIES Foundation.lib OpenMaya.lib OpenMayaAnim.lib OpenMayaUI.lib Qt5Widgets.lib Qt5Gui.lib Qt5Core.lib)
# file(GLOB LIS "${MAYA_LIBRARY_DIR}/*.lib")
# 使用file命令获取指定路径下的所有文件

file(GLOB MY_FILES "${MAYA_LIBRARY_DIR}/*.lib")

# 输出获取到的文件列表
message("Files found in ${PATH_TO_FILES}:")
foreach(FILE ${MY_FILES})
    message("${FILE}")
    set(FILE_LIST ${FILE_LIST} ${FILE})
endforeach()

SET(MAYA_DEFINITIONS _AFXDLL _MBCS NT_PLUGIN REQUIRE_IOSTREAM _BOOL)

set(VCPKG_ROOT "C:\\Users\\17203\\Desktop\\github\\vcpkg")

if(${VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    include(${CMAKE_TOOLCHAIN_FILE})
endif()
find_package(behaviortree_cpp CONFIG REQUIRED)

ADD_LIBRARY(${MAYA_PLUGIN_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${MAYA_PLUGIN_NAME} PRIVATE ${LIBRARIES} BT::behaviortree_cpp action)
# ta(${MAYA_PLUGIN_NAME} PRIVATE ${LIBRARIES})

# 关键：添加action的头文件目录，让编译器能找到ScreenCheck.h
target_include_directories(behaviortree_to_maya_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/action/include  # 指向action的include目录
)

SET_TARGET_PROPERTIES(${MAYA_PLUGIN_NAME} PROPERTIES COMPILE_DEFINITIONS "${MAYA_DEFINITIONS}")
SET_TARGET_PROPERTIES(${MAYA_PLUGIN_NAME} PROPERTIES OUTPUT_NAME "${MAYA_PLUGIN_NAME}")
SET_TARGET_PROPERTIES(${MAYA_PLUGIN_NAME} PROPERTIES SUFFIX ".mll")
SET_TARGET_PROPERTIES(${MAYA_PLUGIN_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

SET_TARGET_PROPERTIES(${MAYA_PLUGIN_NAME} PROPERTIES LINK_FLAGS "/export:initializePlugin /export:uninitializePlugin")