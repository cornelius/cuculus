set(cuculus_SRCS
   mainwindow.cpp
   main.cpp
   cuculusview.cpp
   tweetview.cpp
   imageloader.cpp
   cuculusmodel.cpp
   tweetlistview.cpp
   friendsview.cpp
   friendlabel.cpp
 )

kde4_add_ui_files(cuculus_SRCS prefs_base.ui)

kde4_add_kcfg_files(cuculus_SRCS settings.kcfgc )

kde4_add_executable(cuculus ${cuculus_SRCS})

target_link_libraries(cuculus cuculusclient ${KDE4_KDEUI_LIBS} )

install(TARGETS cuculus DESTINATION ${BIN_INSTALL_DIR} )


########### install files ###############

install( FILES cuculus.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES cuculus.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES cuculusui.rc  DESTINATION  ${DATA_INSTALL_DIR}/cuculus )
