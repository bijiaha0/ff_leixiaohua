add_executable(transcode_aac transcode_aac.c)
target_link_libraries(transcode_aac -lavcodec -lavutil -lavfilter -lavformat -lavdevice -lswscale -lswresample -lpostproc -lSDL2 -lSDL2main)
