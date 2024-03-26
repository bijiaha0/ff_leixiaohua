
add_executable(SourceTest SourceTest.cpp flv.cpp AEncode.cpp MediaControl.cpp AudioDecoder.cpp testFLV.cpp testDecodePath.cpp testMP4Encode.cpp testMeidaControl.cpp testInterface.cpp testFFmpegIO.cpp testConvert.cpp testffmpeg.cpp testDecode.cpp testHead.cpp Transform.cpp testExtraData.cpp testAAC.cpp testADTS.cpp sei_packet.cpp Encode.cpp SEIEncode.cpp testEncode.cpp testEncode2.cpp testEncode3.cpp testDecodeSEI.cpp VideoDecoder.cpp EvoMediaSource.cpp EvoVideoConvert.cpp)

target_link_libraries(SourceTest -lstdc++ -lpthread  -lavcodec -lavutil -lavfilter -lavformat -lavdevice -lswscale -lswresample -lpostproc )
