add_library(libqfv STATIC)

target_sources(libqfv
    PRIVATE
    Descriptions.cpp
    PUBLIC
    FontFeature.cpp
    FontScanner.cpp
    VariableAxis.cpp
)

target_link_libraries(libqfv
    PUBLIC
    ${HARFBUZZ_LIBRARIES}
    Qt6::Quick
    Qt6::Qml
    KF6::I18n
    KF6::I18nQml
)

add_executable(quickfontview)

ecm_add_qml_module(quickfontview
    URI info.mcendu.quickfontview
)

target_sources(quickfontview
    PRIVATE
    main.cpp
)

ecm_target_qml_sources(quickfontview
    SOURCES
    FeaturesDrawer.qml
    FontPage.qml
    FontView.qml
    Main.qml
)

target_link_libraries(quickfontview
    PRIVATE
    libqfv
    Qt6::Quick
    Qt6::Qml
    Qt6::Gui
    Qt6::QuickControls2
    Qt6::Widgets
    KF6::I18n
    KF6::CoreAddons
    KF6::IconThemes
)

install(TARGETS quickfontview ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
