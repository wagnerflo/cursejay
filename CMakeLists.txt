cmake_minimum_required ( VERSION 3.4.1 )
project ( cursejay )

find_package(PkgConfig REQUIRED)
pkg_search_module(TAGLIB REQUIRED taglib)
pkg_search_module(FMT REQUIRED fmt)

add_executable ( cursejay
  src/audio/channel_map.cc
  src/audio/miniaudio.cc
  src/broker.cc
  src/conf.cc
  src/datasrc.cc
  src/db.cc
  src/main.cc
  src/obj.cc
  src/player.cc
  src/ui.cc
)

set_source_files_properties(
  src/audio/miniaudio.cc
  PROPERTIES COMPILE_OPTIONS
  -Wno-conversion
)

target_compile_features( cursejay PRIVATE cxx_std_20 )
target_compile_options( cursejay PRIVATE
  -Wall -Wextra -Wconversion
  ${FMT_CFLAGS_OTHER}
  ${TAGLIB_CFLAGS_OTHER}
)
target_include_directories ( cursejay PRIVATE
  ext/miniaudio
  ext/PolyM/include
  ${FMT_INCLUDE_DIRS}
  ${TAGLIB_INCLUDE_DIRS}
)
target_link_libraries ( cursejay
  dl
  ncurses
  polym
  pthread
  SQLiteCpp
  sqlite3
  m
  ${FMT_LIBRARIES}
  ${TAGLIB_LIBRARIES}
)

option ( SQLITECPP_INTERNAL_SQLITE "" OFF )

add_subdirectory ( ext/SQLiteCpp )
add_subdirectory ( ext/PolyM )
