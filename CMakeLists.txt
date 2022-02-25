#设置CMake最低支持版本
cmake_minimum_required(VERSION 3.17)

#引用ARMClang_Cortex-M4.cmake
include(ARMClang_Cortex-M4.cmake)

#关闭FPU
CMSIS_EnableFPU(TURE)

#设置Sections脚本路径
CMSIS_SetSectionsScriptPath(${CMAKE_HOME_DIRECTORY}/MDK-ARM/STM32L4.sct)

#配置交叉编译
CMSIS_CrossCompilingConfiguration()

#设置工程名
project(STM32L4 C CXX ASM)

#设置C标准版本
set(CMAKE_C_STANDARD 99)

#设置C++标准版本
set(CMAKE_CXX_STANDARD 11)

#添加全局宏定义
add_definitions(-DSTM32L475xx -DUSE_HAL_DRIVER)

#添加头文件引用目录
include_directories(
        Core/Inc
        Drivers/CMSIS/Core/Include
        Drivers/CMSIS/Device/ST/STM32L4xx/Include
        Drivers/STM32L4xx_HAL_Driver/Inc
        Drivers/CMSIS/DSP/Include
        MDK-ARM/RTE/_STM32L4

)

#添加源文件
file(GLOB_RECURSE SOURCES "Core/Src/*.c" "Drivers/STM32L4xx_HAL_Driver/Src/*.c" "MDK-ARM/startup_stm32l475xx.s")

#添加生成可执行文件
add_executable(${PROJECT_NAME}
        ${SOURCES}
        )
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} --text -z $<TARGET_FILE:${PROJECT_NAME}>
        COMMENT "Print memory info")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} --i32 -o  ${HEX_FILE} $<TARGET_FILE:${PROJECT_NAME}>
        COMMAND ${CMAKE_OBJCOPY} --bin -o  ${BIN_FILE} $<TARGET_FILE:${PROJECT_NAME}>
        COMMENT "Building ${HEX_FILE} and Building ${BIN_FILE}")


