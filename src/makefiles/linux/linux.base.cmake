# ------------------------------------------------------------------
# File: src/makefiles/linux/linux.base.cmake
# Purpose: This is the base linux CMake file which sets a bunch of
#    shared flags across all linux builds.
# ------------------------------------------------------------------

# ------------------------------------------------------------------
# Included makefiles
# ------------------------------------------------------------------
include("makefiles/branch/${BRANCH}.cmake")
include("makefiles/shared.cmake")

# ------------------------------------------------------------------
# Hack for Linux CMake.
# ------------------------------------------------------------------
If(NOT CMAKE_BUILD_TYPE)
    Set(CMAKE_BUILD_TYPE Release)
Endif(NOT CMAKE_BUILD_TYPE)

# ------------------------------------------------------------------
# Python directories
# ------------------------------------------------------------------
Set(PYTHONSDK            ${THIRDPARTY_DIR}/python_linux)
Set(PYTHONSDK_INCLUDE    ${PYTHONSDK}/include)
Set(PYTHONSDK_LIB        ${PYTHONSDK}/libs)

# ------------------------------------------------------------------
# Add in the python sdk as an include directory.
# ------------------------------------------------------------------
Include_Directories(
    ${PYTHONSDK_INCLUDE}
)

# ------------------------------------------------------------------
# Link libraries.
# ------------------------------------------------------------------
Set(SOURCEPYTHON_LINK_LIBRARIES
    pthread dl util
    ${DYNCALLSDK_LIB}/libdyncall_s.a
    ${DYNCALLSDK_LIB}/libdyncallback_s.a
    ${DYNCALLSDK_LIB}/libdynload_s.a
)


If(SOURCE_ENGINE MATCHES "bms")
    Set(SOURCEPYTHON_LINK_LIBRARIES
        "${SOURCEPYTHON_LINK_LIBRARIES}"
        ${SOURCESDK_LIB}/public/linux32/mathlib.a
        ${SOURCESDK_LIB}/public/linux32/tier1.a
        ${SOURCESDK_LIB}/public/linux32/tier2.a
        ${SOURCESDK_LIB}/public/linux32/tier3.a
        ${SOURCESDK_LIB}/public/linux32/libtier0_srv.so
        ${SOURCESDK_LIB}/public/linux32/libvstdlib_srv.so
    )
Else()
    Set(SOURCEPYTHON_LINK_LIBRARIES
        "${SOURCEPYTHON_LINK_LIBRARIES}"
        ${SOURCESDK_LIB}/linux/mathlib_i486.a
        ${SOURCESDK_LIB}/linux/tier1_i486.a
    )
EndIf()

# ------------------------------------------------------------------
# Game specific library hacks.
# ------------------------------------------------------------------
If(SOURCE_ENGINE MATCHES "orangebox" OR SOURCE_ENGINE MATCHES "l4d2")
    # Orangebox has all the tier libraries.
    Set(SOURCEPYTHON_LINK_LIBRARIES
        "${SOURCEPYTHON_LINK_LIBRARIES}"
         ${SOURCESDK_LIB}/linux/tier2_i486.a
         ${SOURCESDK_LIB}/linux/tier3_i486.a
         ${SOURCESDK_LIB}/linux/libtier0_srv.so
         ${SOURCESDK_LIB}/linux/libvstdlib_srv.so
    )
EndIf()

If(SOURCE_ENGINE MATCHES "csgo")
    Set(SOURCEPYTHON_LINK_LIBRARIES
        "${SOURCEPYTHON_LINK_LIBRARIES}"
         ${SOURCESDK_LIB}/linux/interfaces_i486.a
         ${SOURCESDK_LIB}/linux/libtier0.so
         ${SOURCESDK_LIB}/linux/libvstdlib.so
         ${SOURCESDK_LIB}/linux32/release/libprotobuf.a
    )
EndIf()

# ------------------------------------------------------------------
# Linux compiler flags.
# ------------------------------------------------------------------
# General definitions
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_LINUX -DPOSIX -DLINUX -DGNUC -DCOMPILER_GCC")

if(SOURCE_ENGINE MATCHES "orangebox" OR SOURCE_ENGINE MATCHES "bms")
    Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNO_MALLOC_OVERRIDE")
Endif()

# Function alias
If(NOT SOURCE_ENGINE MATCHES "bms")
    Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Dstricmp=strcasecmp -D_stricmp=strcasecmp -D_strnicmp=strncasecmp")
    Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Dstrnicmp=strncasecmp -D_snprintf=snprintf")
    Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_vsnprintf=vsnprintf -D_alloca=alloca -Dstrcmpi=strcasecmp")
EndIf()

# Warnings
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-uninitialized -Wno-switch -Wno-unused")
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-non-virtual-dtor -Wno-overloaded-virtual")
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-conversion-null -Wno-write-strings")
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -Wno-reorder")

# Others
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpmath=sse -msse -m32 -fno-strict-aliasing")
Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -fno-threadsafe-statics -v")


# ------------------------------------------------------------------
# Debug / Release compiler flags.
# ------------------------------------------------------------------
If(CMAKE_BUILD_TYPE MATCHES Debug)
    Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG -DBOOST_DEBUG_PYTHON -D_DEBUG -DPy_DEBUG")
Else()
    Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_NDEBUG")
EndIf()

# ------------------------------------------------------------------
# Stub these out because cmake doesn't set debug/release libraries
# correctly...
# ------------------------------------------------------------------
Set(SOURCEPYTHON_LINK_LIBRARIES_RELEASE
    ${PYTHONSDK_LIB}/libpython3.4m.a
    ${BOOSTSDK_LIB}/libboost_python.a
    ${PYTHONSDK_LIB}/libpython3.4m.so.1.0
    ${DYNAMICHOOKSSDK_LIB}/libDynamicHooks.a
    ${ASMJITSDK_LIB}/libAsmJit.a
)

Set(SOURCEPYTHON_LINK_LIBRARIES_DEBUG
    ${PYTHONSDK_LIB}/libpython3.4dm.a
    ${BOOSTSDK_LIB}/libboost_python_d.a
    ${PYTHONSDK_LIB}/libpython3.4dm.so.1.0
    ${DYNAMICHOOKSSDK_LIB}/libDynamicHooks.a
    ${ASMJITSDK_LIB}/libAsmJit_d.a
)
