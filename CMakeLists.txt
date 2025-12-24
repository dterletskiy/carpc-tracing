cmake_minimum_required( VERSION 3.16 FATAL_ERROR )

fenix_project( TARGET ${TARGET_PREFIX}tracing PROJECT TRACING )



###########################################################################################
#                                                                                         #
#                             Compilation include directories                             #
#                                                                                         #
###########################################################################################
include_directories( ${PROJECT_SOURCE_DIR}/api )



###########################################################################################
#                                                                                         #
#                                Linkage include directories                              #
#                                                                                         #
###########################################################################################



###########################################################################################
#                                                                                         #
#                                   Compile definitions                                   #
#                                                                                         #
###########################################################################################



###########################################################################################
#                                                                                         #
#                                      Code generation                                    #
#                                                                                         #
###########################################################################################
find_files_by_ext( RECURSE FILES PLANTUML_FILES
      LOCATION ${PROJECT_SOURCE_DIR}
      EXTENTIONS ${EXTENTIONS_PLANTUML}
   )
generate_plantumls( PLANTUML_FILES ${PLANTUML_FILES} GENERATED_FILES PROJECT_GEN_PLANTUML_FILES )



###########################################################################################
#                                                                                         #
#                                   Build source file list                                #
#                                                                                         #
###########################################################################################
find_files_by_ext( RECURSE FILES PROJECT_SOURCE_FILES
      LOCATION ${PROJECT_SOURCE_DIR}
      EXTENTIONS ${EXTENTIONS_CPP_SRC}
   )



###########################################################################################
#                                                                                         #
#                                      Debug messages                                     #
#                                                                                         #
###########################################################################################
print_variables( )



add_library(
      ${PROJECT_TARGET_NAME}-shared SHARED
      ${PROJECT_SOURCE_FILES}
   )
set_target_properties(
      ${PROJECT_TARGET_NAME}-shared PROPERTIES
      OUTPUT_NAME ${PROJECT_TARGET_NAME}
   )

add_library(
      ${PROJECT_TARGET_NAME}-static STATIC
      ${PROJECT_SOURCE_FILES}
   )
set_target_properties(
      ${PROJECT_TARGET_NAME}-static PROPERTIES
      OUTPUT_NAME ${PROJECT_TARGET_NAME}
   )

if( DLT_TRACE )
   target_link_libraries( ${PROJECT_TARGET_NAME}-shared PUBLIC dlt )
   target_link_libraries( ${PROJECT_TARGET_NAME}-static PUBLIC dlt )
endif( )
if( ${OS_TARGET} EQUAL ${OS_ANDROID} )
   target_link_libraries( ${PROJECT_TARGET_NAME}-shared PUBLIC log )
   target_link_libraries( ${PROJECT_TARGET_NAME}-static PUBLIC log )
endif( )

add_custom_target( "${PROJECT_TARGET_NAME}-documentation" ALL
      COMMENT "cmake ${PROJECT_TARGET_NAME}-documentation"
      DEPENDS ${PROJECT_GEN_PLANTUML_FILES}
   )

add_custom_target(
      ${PROJECT_TARGET_NAME} ALL
      DEPENDS
         ${PROJECT_TARGET_NAME}-shared
         ${PROJECT_TARGET_NAME}-static
         ${PROJECT_TARGET_NAME}-documentation
   )



fenix_add_deploy_targets( NAME ${PROJECT_TARGET_NAME}
      SUBDIR_TARGETS carpc
      SUBDIR_INCLUDES carpc
      SUBDIR_CONFIGS carpc
      TARGETS
         ${PROJECT_TARGET_NAME}-static
         ${PROJECT_TARGET_NAME}-shared
      INCLUDES
         ${PROJECT_SOURCE_DIR}/api/carpc/
      CONFIGS
         ${PROJECT_SOURCE_DIR}/dlt.conf
   )
