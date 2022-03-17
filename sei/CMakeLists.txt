
aux_source_directory(../sei DIR_SRCS)
add_executable(SourceTest ${DIR_SRCS})

target_link_libraries(SourceTest -lavcodec -lavutil -lavfilter -lavformat -lavdevice -lswscale -lswresample)
