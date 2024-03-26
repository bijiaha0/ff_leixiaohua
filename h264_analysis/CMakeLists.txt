add_executable(h264_analyze h264_analyze.cpp h264_avcc.cpp h264_sei.cpp h264_stream.cpp NALParse.cpp)
target_link_libraries(h264_analyze -lstdc++ -lpthread  -lavcodec -lavutil -lavfilter -lavformat -lavdevice -lswscale -lswresample -lpostproc )
