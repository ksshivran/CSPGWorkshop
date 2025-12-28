set(lab01_optional_goose_publisher_SRCS
   lab01_optional_goose_publisher.c
)

IF(MSVC)

set_source_files_properties(${lab01_optional_goose_publisher_SRCS}
                                       PROPERTIES LANGUAGE CXX)
ENDIF(MSVC)                                       
                                       
add_executable(lab01_optional_goose_publisher
  ${lab01_optional_goose_publisher_SRCS}
)

target_link_libraries(lab01_optional_goose_publisher
    iec61850
)


