# CMakeLists.txt for BlinkLED

# 添加模块目录到 xr 的 include 路径
target_include_directories(xr PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# 自动收集所有 .cpp / .c 文件并加入 xr 目标
file(GLOB MODULE_BLINKLED_SRC
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/*.c"
)

target_sources(xr PRIVATE ${MODULE_BLINKLED_SRC})
