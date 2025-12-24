set(lab01_optional_goose_subscriber_SRCS
  lab01_optional_goose_subscriber.c
)

IF(MSVC)

set_source_files_properties(${lab01_optional_goose_subscriber_SRCS}
                                       PROPERTIES LANGUAGE CXX)
ENDIF(MSVC)
                                       
add_executable(lab01_optional_goose_subscriber
  ${lab01_optional_goose_subscriber_SRCS}
)

target_link_libraries(lab01_optional_goose_subscriber
    iec61850
)


