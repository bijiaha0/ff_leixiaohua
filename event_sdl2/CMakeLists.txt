add_executable(event_sdl2 event_sdl2.cpp)
target_link_libraries(event_sdl2 -lavcodec -lavutil -lavfilter -lavformat -lavdevice -lswscale -lswresample -lpostproc -lSDL2 -lSDL2main)
