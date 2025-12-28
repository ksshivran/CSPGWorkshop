set(lab03_goose_publisher_hmac_SRCS 
    lab03_goose_publisher_hmac.c
)

IF(MSVC)

set_source_files_properties(${lab03_goose_publisher_hmac_SRCS}
                                       PROPERTIES LANGUAGE CXX)
ENDIF(MSVC)
                                       

add_executable(lab03_goose_publisher_hmac 
        ${lab03_goose_publisher_hmac_SRCS}
)
target_link_libraries(lab03_goose_publisher_hmac
        iec61850
)
