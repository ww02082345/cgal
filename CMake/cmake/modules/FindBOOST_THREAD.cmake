# Try to find the BOOST_THREAD library
# BOOST_THREAD_FOUND	    - system has BOOST_THREAD lib
# BOOST_THREAD_LIBRARIES   - libraries needed to use BOOST_THREAD

# TODO: support MacOSX

# BOOST_THREAD needs Boost
INCLUDE(FindPackageHandleStandardArgs)

find_package(Boost2 QUIET)
if(Boost_FOUND AND Boost_LIBRARY_DIRS)
  if (BOOST_THREAD_LIBRARIES)
      # Already in cache, be silent
      set(BOOST_THREAD_FIND_QUIETLY TRUE)
  endif()

  if ( AUTO_LINK_ENABLED )
    set(BOOST_THREAD_LIBRARIES "")
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(BOOST_THREAD "boost_thread not found." Boost_LIBRARY_DIRS )
  else()
    find_library(BOOST_THREAD_LIBRARIES NAMES boost_thread PATHS ${Boost_LIBRARY_DIRS})
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(BOOST_THREAD "boost_thread not found." BOOST_THREAD_LIBRARIES )
  endif()
endif()

