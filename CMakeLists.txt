# This CMakeLists.txt file is adapted from the one for the similar project
# DiffPDF, found at: https://gitlab.com/eang/diffpdf/

cmake_minimum_required(VERSION 3.1)

set(COMPAREPDF_VERSION 1.2.0)
set(COMPAREPDF_DATE 2019-12-19)
project(comparepdf VERSION ${COMPAREPDF_VERSION})

set(QT_MIN_VERSION 5.7.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(ECMSetupVersion)
include(FeatureSummary)
include(GNUInstallDirs)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS
    Core
    Gui
    Widgets)

find_package(Poppler REQUIRED COMPONENTS Core Qt5)

set(comparepdf_SRCS
    main.cpp
    option_parser.cpp)

ecm_setup_version(PROJECT
    VARIABLE_PREFIX COMPAREPDF
    VERSION_HEADER comparepdfversion.h)

configure_file(comparepdf.1.cmake comparepdf.1)

qt5_add_resources(comparepdf_SRCS)

add_executable(comparepdf ${comparepdf_SRCS})

target_link_libraries(comparepdf
    Poppler::Qt5
    Qt5::Widgets)

target_compile_definitions(comparepdf PRIVATE -DPOPPLER_VERSION="${Poppler_VERSION}")

install(FILES README.md CHANGES.md DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(TARGETS comparepdf DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${CMAKE_BINARY_DIR}/comparepdf.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
