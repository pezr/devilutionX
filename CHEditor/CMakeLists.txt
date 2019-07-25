find_package(SDL2_image REQUIRED)

configure_file("Anonymous\ Pro.ttf" "../Anonymous\ Pro.ttf" COPYONLY)

add_executable(cheditor
    ../SourceX/dx.cpp
    ../SourceX/miniwin/misc.cpp
    ../SourceX/miniwin/misc_io.cpp
    ../SourceX/miniwin/misc_msg.cpp
    ../SourceX/miniwin/misc_dx.cpp
    ../SourceX/miniwin/rand.cpp
    ../SourceX/miniwin/thread.cpp
    ../SourceX/miniwin/dsound.cpp
    ../SourceX/miniwin/ddraw.cpp
    ../SourceX/sound.cpp
    ../SourceX/storm/storm.cpp
    ../SourceX/storm/storm_net.cpp
    ../SourceX/storm/storm_dx.cpp
    ../SourceX/dvlnet/abstract_net.cpp
    ../SourceX/dvlnet/loopback.cpp
    ../SourceX/dvlnet/packet.cpp
    ../SourceX/dvlnet/base.cpp
    ../SourceX/dvlnet/frame_queue.cpp
    ../SourceX/dvlnet/tcp_client.cpp
    ../SourceX/dvlnet/tcp_server.cpp
    ../SourceX/dvlnet/udp_p2p.cpp
    ../SourceX/DiabloUI/credits.cpp
    ../SourceX/DiabloUI/diabloui.cpp
    ../SourceX/DiabloUI/dialogs.cpp
    ../SourceX/DiabloUI/mainmenu.cpp
    ../SourceX/DiabloUI/progress.cpp
    ../SourceX/DiabloUI/selconn.cpp
    ../SourceX/DiabloUI/selgame.cpp
    ../SourceX/DiabloUI/selhero.cpp
    ../SourceX/DiabloUI/title.cpp
    cheditor.cpp
    )

target_include_directories(cheditor PRIVATE
  ../Source
  ../SourceX
  ../SourceS
  ../DiabloUI
  ../3rdParty/asio/include
  ../3rdParty/Radon/Radon/include
  ../3rdParty/libsmacker
  )

target_link_libraries(cheditor PRIVATE
  devilution
  PKWare
  StormLib
  smacker
  Radon
  SDL2::SDL2main
  SDL2::SDL2_ttf
  SDL2::SDL2_mixer
  SDL2::SDL2_image
  sodium
  ncurses
  )

target_compile_definitions(cheditor PRIVATE ASIO_STANDALONE)

# if(NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  # target_compile_options(cheditor PRIVATE -Wall -Wextra -Wno-write-strings -Wno-multichar -Wno-unused-parameter)
  # target_compile_options(cheditor PRIVATE -fsigned-char)
# endif()

# if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # target_compile_options(cheditor PRIVATE -Wno-parentheses -Wno-logical-op-parentheses -Wno-bitwise-op-parentheses)
  # target_compile_options(cheditor PRIVATE -Wno-ignored-attributes)
# endif()

