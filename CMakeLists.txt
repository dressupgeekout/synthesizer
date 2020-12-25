cmake_minimum_required(VERSION 3.0)
project(synthesizer)

add_executable(synthesizer
  main.c
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  target_compile_options(synthesizer PLATFORM_WINDOWS)

  set(SDL2_INCLUDE_DIR /Users/charlotte/Downloads/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2)
  set(SDL2_LIBDIR /Users/charlotte/Downloads/SDL2-2.0.12/x86_64-w64-mingw32/lib) 

  set(FLUIDSYNTH_INCLUDE_DIR /Users/charlotte/Downloads/fluidsynth-x64/include)
  set(FLUIDSYNTH_LIBDIR /Users/charlotte/Downloads/fluidsynth-x64/lib)

  set(SDL2_LIBRARY /Users/charlotte/Downloads/SDL2-2.0.12/x86_64-w64-mingw32/lib/libSDL2.a)
  set(SDL2_LIBRARY2  /Users/charlotte/Downloads/SDL2-2.0.12/x86_64-w64-mingw32/lib/libSDL2main.a)
  set(SDL2_LIBRARY3  /Users/charlotte/Downloads/SDL2-2.0.12/x86_64-w64-mingw32/lib/libSDL2_test.a)
  find_library(FLUIDSYNTH_LIBRARY fluidsynth PATHS ${FLUIDSYNTH_LIBDIR})

  #set(SDL2_LIBRARY /Users/charlotte/Downloads/SDL2-2.0.12/x86_64-w64-mingw32/lib/libSDL2.a)
  #set(FLUIDSYNTH_LIBRRARY /Users/charlotte/Downloads/fluidsynth-x64/bin/libfluidsynth-2.dll)

  set(INCLUDE_DIRS ${SDL2_INCLUDE_DIR} ${FLUIDSYNTH_INCLUDE_DIR}) 
  set(LIBRARIES mingw32 ${SDL2_LIBRARY} ${SDL2_LIBRARY2} ${SDL2_LIBRARY3} ${FLUIDSYNTH_LIBRARY} ws2_32 winmm user32 dinput8 gdi32 imm32 ole32 oleaut32 shell32 setupapi uuid dxerr8 dxguid version)
else()
  include(FindPkgConfig)
  pkg_check_modules(SDL2 REQUIRED sdl2)

  set(LIBFLUIDSYNTH ${CMAKE_CURRENT_LIST_DIR}/../fluidsynth/build/src/libfluidsynth.dylib)
  set(FLUIDSYNTH_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../fluidsynth/include)

  set(INCLUDE_DIRS ${SDL2_INCLUDE_DIRS} ${FLUIDSYNTH_INCLUDE_DIR})
  set(LIBRARIES ${SDL2_LIBRARIES} ${LIBFLUIDSYNTH})
endif()


target_include_directories(synthesizer SYSTEM PUBLIC ${INCLUDE_DIRS})
target_link_libraries(synthesizer ${LIBRARIES})

