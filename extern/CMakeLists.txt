# SDL
# https://github.com/libsdl-org/SDL
set( SDL_LIBC ON CACHE BOOL "" FORCE )
set( SDL_TEST OFF CACHE BOOL "" FORCE )
add_subdirectory( SDL )
target_link_libraries( ${PROJECT_NAME} SDL3::SDL3)

# SDL_ttf
# https://github.com/libsdl-org/SDL_ttf
set( SDL3TTF_SAMPLES OFF CACHE BOOL "" FORCE )
set( SDL3TTF_INSTALL OFF CACHE BOOL "" FORCE )
set( SDL3TTF_VENDORED ON CACHE BOOL "" FORCE )
set( SDL3TTF_HARFBUZZ ON CACHE BOOL "" FORCE )
add_subdirectory( SDL_ttf )
target_link_libraries( ${PROJECT_NAME} SDL3_ttf::SDL3_ttf )

# SDL_mixer
# https://github.com/libsdl-org/SDL_mixer
set( SDL3MIXER_SAMPLES OFF CACHE BOOL "" FORCE )
set( SDL3MIXER_INSTALL OFF CACHE BOOL "" FORCE )
set( SDL3MIXER_VENDORED ON CACHE BOOL "" FORCE )
set( SDL3MIXER_DEPS_SHARED OFF CACHE BOOL "" FORCE )
set( SDL3MIXER_FLAC OFF CACHE BOOL "" FORCE )
set( SDL3MIXER_MOD OFF CACHE BOOL "" FORCE )
set( SDL3MIXER_MP3 OFF CACHE BOOL "" FORCE )
set( SDL3MIXER_MIDI OFF CACHE BOOL "" FORCE )
set( SDL3MIXER_OPUS OFF CACHE BOOL "" FORCE )
add_subdirectory( SDL_mixer )
target_link_libraries( ${PROJECT_NAME} SDL3_mixer::SDL3_mixer )