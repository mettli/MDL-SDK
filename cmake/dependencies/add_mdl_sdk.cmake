# -------------------------------------------------------------------------------------------------
# script expects the following variables:
# - __TARGET_ADD_DEPENDENCY_TARGET
# - __TARGET_ADD_DEPENDENCY_DEPENDS
# - __TARGET_ADD_DEPENDENCY_COMPONENTS
# - __TARGET_ADD_DEPENDENCY_NO_RUNTIME_COPY
# - __TARGET_ADD_DEPENDENCY_NO_LINKING
# -------------------------------------------------------------------------------------------------

# add include directories, wo do not link in general as the shared libraries are loaded manually
target_include_directories(${__TARGET_ADD_DEPENDENCY_TARGET} 
    PRIVATE
        $<TARGET_PROPERTY:mdl::mdl_sdk,INTERFACE_INCLUDE_DIRECTORIES>
    )

# copy runtime dependencies
# copy system libraries only on windows
if(NOT __TARGET_ADD_DEPENDENCY_NO_RUNTIME_COPY)
    if(WIN32)
        target_copy_to_output_dir(TARGET ${__TARGET_ADD_DEPENDENCY_TARGET}
            FILES       
                "$<TARGET_FILE:mdl::mdl_sdk>"
                "$<TARGET_FILE:mdl::dds>"
                "$<TARGET_FILE:mdl::nv_freeimage>"
                "$<TARGET_FILE_DIR:mdl::nv_freeimage>/${CMAKE_SHARED_LIBRARY_PREFIX}freeimage${CMAKE_SHARED_LIBRARY_SUFFIX}"
            )
    endif()
endif()
