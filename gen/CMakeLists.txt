add_executable(hdr_sdr_gen hdr_sdr_gen.cpp)
target_link_libraries(hdr_sdr_gen -lpthread)



add_executable(hdr_sdr hdr_sdr.cpp)
target_link_libraries(hdr_sdr -lpthread)