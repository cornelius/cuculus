set(cuculusclient_SRCS
   status.cpp
   statusparser.cpp
   statuslistjob.cpp
 )

kde4_add_library(cuculusclient SHARED ${cuculusclient_SRCS})
set_target_properties(cuculusclient PROPERTIES VERSION ${KDE_GENERIC_LIB_VERSION} SOVERSION ${KDE_GENERIC_LIB_SOVERSION})

target_link_libraries(cuculusclient ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KDE4_KABC_LIBS})

install(TARGETS cuculusclient DESTINATION ${LIB_INSTALL_DIR})
