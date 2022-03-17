cmake_minimum_required(VERSION 3.20)
project(ff_leixiaohua)

set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/local/Cellar/sdl2/2.0.18/include/)
link_directories(/usr/local/Cellar/sdl2/2.0.18/lib)

include_directories(/usr/local/Cellar/ffmpeg/4.4.1_3/include)
link_directories(/usr/local/Cellar/ffmpeg/4.4.1_3/lib)

add_subdirectory(simplest_ffmpeg_player)
add_subdirectory(simplest_ffmpeg_player_su)
add_subdirectory(simplest_ffmpeg_helloworld)
add_subdirectory(simplest_video_play_sdl2)
add_subdirectory(simplest_ffmpeg_decoder_pure)
add_subdirectory(simplest_ffmpeg_decoder)
add_subdirectory(event_sdl2)
add_subdirectory(simplest_video_play_sdl2_basic)
add_subdirectory(simplest_mediadata_test)
add_subdirectory(sei)
