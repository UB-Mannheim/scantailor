
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/core")

SET(
        cli_only_sources
        ConsoleBatch.cpp ConsoleBatch.h
        main-cli.cpp
)

ADD_EXECUTABLE(scantailor-cli-ubma ${cli_only_sources} )

TARGET_LINK_LIBRARIES(
        scantailor-cli-ubma
        fix_orientation page_split deskew select_content page_layout output stcore
	dewarping zones interaction imageproc math foundation exporting
)

# Widgets module is used statically but not at runtime.
QT5_USE_MODULES(scantailor-cli-ubma Widgets Xml)

IF(EXTRA_LIBS)
        TARGET_LINK_LIBRARIES(scantailor-cli-ubma ${EXTRA_LIBS})
ENDIF()

IF(APPLE)
        INSTALL(TARGETS scantailor-cli-ubma BUNDLE DESTINATION . RUNTIME DESTINATION bin)
ELSE(APPLE)
        INSTALL(TARGETS scantailor-cli-ubma RUNTIME DESTINATION bin)
ENDIF(APPLE)
