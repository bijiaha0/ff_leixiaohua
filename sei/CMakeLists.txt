
add_executable(SourceTest SourceTest.cpp sei_packet.cpp Encode.cpp SEIEncode.cpp testEncode.cpp testEncode2.cpp testEncode3.cpp testDecodeSEI.cpp VideoDecoder.cpp EvoMediaSource.cpp EvoVideoConvert.cpp)

target_link_libraries(SourceTest -lstdc++ -lpthread  -lavcodec -lavutil -lavfilter -lavformat -lavdevice -lswscale -lswresample -lpostproc )
