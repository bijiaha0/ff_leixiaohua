cmake_minimum_required(VERSION 3.22.1)
project(ff_leixiaohua)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/Cellar/ffmpeg/7.0.1-with-options_1/include/)
link_directories(/usr/local/Cellar/ffmpeg/7.0.1-with-options_1/lib/)

include_directories(/usr/local/Cellar/boost/1.82.0_1/include)
link_directories(/usr/local/Cellar/boost/1.82.0_1/lib/)

include_directories(/Users/bijh/Documents/acl-master/dist/include/)
link_directories(/Users/bijh/Documents/acl-master/dist/lib/macos/)

include_directories(${PROJECT_SOURCE_DIR}/agora_sdk/include)
#link_directories(${PROJECT_SOURCE_DIR}/ffmpeg/lib)

include_directories(/Users/bijh/Desktop/sourcecode/project/public)
link_directories(/Users/bijh/Desktop/sourcecode/project/public)

#add_subdirectory(simplest_ffmpeg_player)
#add_subdirectory(simplest_ffmpeg_player_su)
add_subdirectory(simplest_ffmpeg_helloworld)
#add_subdirectory(simplest_video_play_sdl2)
#add_subdirectory(simplest_ffmpeg_decoder_pure)
#add_subdirectory(simplest_ffmpeg_decoder)
#add_subdirectory(event_sdl2)
#add_subdirectory(simplest_video_play_sdl2_basic)
#add_subdirectory(simplest_mediadata_test)
#add_subdirectory(sei)
#add_subdirectory(h264_analysis)
#add_subdirectory(transcode_aac)

#add_subdirectory(agora_sdk_yuv_pcm)
#add_subdirectory(houjie/complex)
#add_subdirectory(houjie/ex)
#add_subdirectory(houjie/sample)
#add_subdirectory(houjie/string)
#
#
#
#add_subdirectory(daniu/chapter1)
#add_subdirectory(daniu/chapter2)
#add_subdirectory(daniu/chapter3)
#add_subdirectory(daniu/chapter4/demo4-1)
#add_subdirectory(daniu/chapter4/demo4-2)
#add_subdirectory(daniu/chapter4/demo4-3)
#add_subdirectory(daniu/chapter4/demo4-4)
#add_subdirectory(daniu/chapter4/demo4-5)
#
#add_subdirectory(daniu/AboutCasts)
#add_subdirectory(daniu/AboutCharArray)
#add_subdirectory(daniu/AboutDisplacement)
#add_subdirectory(daniu/AboutNumberOverflow)
#add_subdirectory(daniu/AboutString)
#add_subdirectory(daniu/AboutString2)
#
#
#add_subdirectory(daniu/chapter5/demo5-1)
#add_subdirectory(daniu/chapter5/demo5-2)
#add_subdirectory(daniu/chapter5/demo5-3)
#add_subdirectory(daniu/chapter5/demo5-4)
#add_subdirectory(daniu/chapter5/demo5-5)
#add_subdirectory(daniu/chapter5/demo5-6)
#add_subdirectory(daniu/chapter5/demo5-7)
#add_subdirectory(daniu/chapter5/demo5-8)
#add_subdirectory(daniu/chapter5/demo5-9)
#add_subdirectory(daniu/chapter5/demo5-10)
#add_subdirectory(daniu/chapter5/demo5-11)
#add_subdirectory(daniu/chapter5/demo5-12)
#
#
#add_subdirectory(daniu/chapter6/demo6-1)
#add_subdirectory(daniu/chapter6/demo6-2)
#add_subdirectory(daniu/chapter6/demo6-3)
#add_subdirectory(daniu/chapter6/demo6-4)
#add_subdirectory(daniu/chapter6/demo6-5)
#add_subdirectory(daniu/chapter6/demo6-6)
#add_subdirectory(daniu/chapter6/demo6-7)
#add_subdirectory(daniu/chapter6/demo6-8)
#add_subdirectory(daniu/chapter6/demo6-9)
#
#
#add_subdirectory(daniu/chapter7/demo7-1)
#add_subdirectory(daniu/chapter7/demo7-2)
#add_subdirectory(daniu/chapter7/demo7-3)
#add_subdirectory(daniu/chapter7/demo7-4)
#
#
#add_subdirectory(daniu/chapter8/demo8-1)
#add_subdirectory(daniu/chapter8/demo8-2)
#add_subdirectory(daniu/chapter8/demo8-3)
#add_subdirectory(daniu/chapter8/demo8-4)
#add_subdirectory(daniu/chapter8/demo8-5)
#add_subdirectory(daniu/chapter8/demo8-6)
#add_subdirectory(daniu/chapter8/demo8-7)

#add_subdirectory(daniu/chapter9/demo9-1)
#add_subdirectory(daniu/chapter9/demo9-2)
#add_subdirectory(daniu/chapter9/demo9-3)
#add_subdirectory(daniu/chapter9/demo9-4)
#add_subdirectory(daniu/chapter9/demo9-5)
#add_subdirectory(daniu/chapter9/demo9-6)
#add_subdirectory(daniu/chapter9/demo9-7)
#add_subdirectory(daniu/chapter9/demo9-8)
#add_subdirectory(daniu/chapter9/demo9-9)
#add_subdirectory(daniu/chapter9/demo9-10)
#add_subdirectory(daniu/chapter9/demo9-11)
#add_subdirectory(daniu/chapter9/MyGC)

#add_subdirectory(opencv_test)

#add_subdirectory(cpp-primer-plus-6th/cpp_source/ch01)
#add_subdirectory(cpp-primer-plus-6th/cpp_source/ch02)
#add_subdirectory(cpp-primer-plus-6th/cpp_source/ch03)

#add_subdirectory(ModernCppCampC/day)
#add_subdirectory(ModernCppCampC/module2)
add_subdirectory(acl)
#add_subdirectory(wucongzhou)
#add_subdirectory(gen)