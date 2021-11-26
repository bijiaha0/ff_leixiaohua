add_executable(simplest_ffmpeg_decoder_pure simplest_ffmpeg_decoder_pure.cpp)
target_link_libraries(simplest_ffmpeg_decoder_pure -lavcodec -lavutil -lavfilter -lavformat -lavdevice -lswscale -lswresample -lpostproc -lSDL2 -lSDL2main)
