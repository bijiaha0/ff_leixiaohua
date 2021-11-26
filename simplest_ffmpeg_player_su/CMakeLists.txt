add_executable(simplest_ffmpeg_player_su simplest_ffmpeg_player_su.cpp)
target_link_libraries(simplest_ffmpeg_player_su -lavcodec -lavutil -lavfilter -lavformat -lavdevice -lswscale -lswresample -lpostproc -lSDL2 -lSDL2main)
