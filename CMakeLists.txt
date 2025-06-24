cmake_minimum_required(VERSION 3.26)
project(quickfontview)
ENABLE_TESTING()

set(CMAKE_CXX_STANDARD 20)

find_package(ECM 6.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMFindQmlModule)
include(ECMQmlModule)
include(KDEClangFormat)

find_package(PkgConfig REQUIRED)

find_package(Qt6 6.7 REQUIRED COMPONENTS
    Core
    Quick
    Test
    Gui
    QuickControls2
    Widgets
)

find_package(KF6 REQUIRED COMPONENTS
    Kirigami
    I18n
    CoreAddons
    QQC2DesktopStyle
    IconThemes
)

pkg_check_modules(HARFBUZZ REQUIRED harfbuzz)

ecm_find_qmlmodule(org.kde.kirigami REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)

file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h *.hpp *.c)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})

install(PROGRAMS info.mcendu.quickfontview DESTINATION ${KDE_INSTALL_APPDIR})

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
