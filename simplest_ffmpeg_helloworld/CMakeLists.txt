add_executable(simplest_ffmpeg_helloworld simplest_ffmpeg_helloworld.cpp)
target_link_libraries(simplest_ffmpeg_helloworld -lavcodec -lavutil -lavfilter -lavformat -lavdevice -lswscale -lswresample -lpostproc -lSDL2 -lSDL2main)
