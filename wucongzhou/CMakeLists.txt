add_executable(crtsurfdata crtsurfdata.cpp _public.h _public.cpp)
target_link_libraries(crtsurfdata -l_public)

add_executable(checkproc checkproc.cpp _public.h _public.cpp)
target_link_libraries(checkproc -l_public)

add_executable(ftpgetfiles ftpgetfiles.cpp _ftp.h _ftp.cpp)
target_link_libraries(ftpgetfiles -lftp)