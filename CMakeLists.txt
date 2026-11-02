cmake_minimum_required(VERSION 3.16)

project(tubularix VERSION 0.5.1.7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt5: the QtGui module was split up. Everything the game uses from QtGui in
# Qt4 (QApplication, QMainWindow, QDialog, QAction, ...) now lives in
# QtWidgets, so the widgets module has to be requested explicitly.
#5.12 is the real minimum: QRandomGenerator (5.10) and
#QFontMetrics::horizontalAdvance() (5.11) are used instead of the deprecated
#qrand()/qsrand() and QFontMetrics::width().
find_package(Qt5 5.12 REQUIRED COMPONENTS Widgets Network)

set(tubularix_SOURCES
    src/src/main.cpp
    src/src/mainwindow.cpp
    src/src/gameboard.cpp
    src/src/piece.cpp
    src/src/gametypedialog.cpp
    src/src/gameoptionsdialog.cpp
    src/src/keyselectionbutton.cpp
    src/src/piececolorselection.cpp
    src/src/networkserverdialog.cpp
    src/src/networkclientdialog.cpp
    src/src/gamecolors.cpp
)

set(tubularix_HEADERS
    src/src/mainwindow.h
    src/src/gameboard.h
    src/src/piece.h
    src/src/gametypedialog.h
    src/src/gameoptionsdialog.h
    src/src/keyselectionbutton.h
    src/src/piececolorselection.h
    src/src/networkserverdialog.h
    src/src/networkclientdialog.h
    src/src/gamecolors.h
)

set(tubularix_FORMS
    src/ui/mainwindow.ui
    src/ui/gametypedialog.ui
    src/ui/gameoptionsdialog.ui
    src/ui/networkserverdialog.ui
    src/ui/networkclientdialog.ui
)

set(tubularix_RESOURCES
    src/tubularix.qrc
)

# The sources include the forms as "ui_<name>.h"; qt5_wrap_ui generates those
# headers in the binary directory, which is on the target's include path.
qt5_wrap_ui(tubularix_UI_HEADERS ${tubularix_FORMS})

add_executable(tubularix
    ${tubularix_SOURCES}
    ${tubularix_HEADERS}
    ${tubularix_UI_HEADERS}
    ${tubularix_RESOURCES}
)

target_include_directories(tubularix PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(tubularix PRIVATE Qt5::Widgets Qt5::Network)

# Translations are compiled next to the executable so the game can be run
# straight from the build tree. lrelease comes with qttools (qt5_tools on
# Haiku); if it is not installed, the .qm files that already exist in the
# source tree are copied instead.
set(tubularix_TS_FILES
    src/translations/tubularix_cs.ts
    src/translations/tubularix_es.ts
    src/translations/tubularix_gl.ts
)

find_package(Qt5LinguistTools QUIET)
if(Qt5LinguistTools_FOUND)
    qt5_add_translation(tubularix_QM_FILES ${tubularix_TS_FILES})
    add_custom_target(tubularix_translations ALL DEPENDS ${tubularix_QM_FILES})
    add_dependencies(tubularix tubularix_translations)
else()
    file(GLOB tubularix_PREBUILT_QM_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/translations/*.qm")
    foreach(qm_file ${tubularix_PREBUILT_QM_FILES})
        get_filename_component(qm_name "${qm_file}" NAME)
        configure_file("${qm_file}" "${CMAKE_CURRENT_BINARY_DIR}/${qm_name}" COPYONLY)
    endforeach()
endif()
