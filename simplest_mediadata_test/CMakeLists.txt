
# set out direcroty
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/simplest_mediadata_test)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/simplest_mediadata_test)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/simplest_mediadata_test)

# copy test file
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cie1931_500x500.rgb
        colorbar_640x360.rgb
        lena_256x256_rgb24.rgb
        DESTINATION  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lena_256x256_yuv444p.yuv
        lena_distort_256x256_yuv420p.yuv
        graybar_640x360.yuv
        lena_256x256_yuv420p.yuv
        DESTINATION  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sintel.h264
        nocturne.aac
        cuc_ieschool.flv
        drum.pcm
        NocturneNo2inEflat_44.1k_s16le.pcm
        DESTINATION  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

aux_source_directory(. srcs)
add_executable(simplest_mediadata_test ${srcs})


