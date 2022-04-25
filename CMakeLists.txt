cmake_minimum_required ( VERSION 3.4.1 )
project ( cursejay )

add_executable ( cursejay
  # src/mat.cc
  src/main.cc
  src/conf.cc
  src/db.cc
  src/ui.cc
  src/obj.cc
)

target_compile_features( cursejay PUBLIC cxx_std_17 )
target_compile_options( cursejay PRIVATE -Wall -Wextra -Wconversion  )
target_include_directories ( cursejay PUBLIC
  ext/cxxcurses/include
  ext/miniaudio
  ext/PolyM/include
)
target_link_libraries ( cursejay
  ncurses
  SQLiteCpp
  sqlite3
  pthread
  dl
  polym
  tag
  m
)

option ( SQLITECPP_INTERNAL_SQLITE "" OFF )

add_subdirectory ( ext/oboe )
add_subdirectory ( ext/SQLiteCpp )
add_subdirectory ( ext/PolyM )
