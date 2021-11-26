add_executable(simplest_ffmpeg_player simplest_ffmpeg_player.cpp)
target_link_libraries(simplest_ffmpeg_player -lavcodec -lavutil -lavfilter -lavformat -lavdevice -lswscale -lswresample -lpostproc -lSDL2 -lSDL2main)
