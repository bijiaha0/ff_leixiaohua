add_executable(simplest_ffmpeg_decoder simplest_ffmpeg_decoder.cpp)
target_link_libraries(simplest_ffmpeg_decoder -lavcodec -lavutil -lavfilter -lavformat -lavdevice -lswscale -lswresample -lpostproc -lSDL2 -lSDL2main)
