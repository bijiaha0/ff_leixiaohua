add_executable(simplest_video_play_sdl2 simplest_video_play_sdl2.cpp)
target_link_libraries(simplest_video_play_sdl2 -lavcodec -lavutil -lavfilter -lavformat -lavdevice -lswscale -lswresample -lpostproc -lSDL2 -lSDL2main)
