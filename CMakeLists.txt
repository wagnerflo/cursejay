cmake_minimum_required ( VERSION 3.4.1 )
project ( cursejay )

find_package(PkgConfig REQUIRED)
pkg_search_module(TAGLIB REQUIRED taglib)

add_executable ( cursejay
  src/main.cc
  src/conf.cc
  src/db.cc
  src/ui.cc
  src/obj.cc
  src/player.cc
  src/miniaudio.cc
)

set_source_files_properties(
  src/miniaudio.cc
  PROPERTIES COMPILE_OPTIONS
  -Wno-conversion
)

target_compile_features( cursejay PRIVATE cxx_std_17 )
target_compile_options( cursejay PRIVATE
  -Wall -Wextra -Wconversion
  ${TAGLIB_CFLAGS_OTHER}
)
target_include_directories ( cursejay PRIVATE
  ext/cxxcurses/include
  ext/miniaudio
  ext/PolyM/include
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
  ${TAGLIB_LIBRARIES}
)

option ( SQLITECPP_INTERNAL_SQLITE "" OFF )

add_subdirectory ( ext/SQLiteCpp )
add_subdirectory ( ext/PolyM )
