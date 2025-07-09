cmake_minimum_required(VERSION 3.16)

project(QtHelper VERSION 0.1 LANGUAGES CXX)

# 设置 C++20 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appQtHelper
    main.cpp
)

qt_add_qml_module(appQtHelper
    URI QtHelper
    VERSION 1.0
    QML_FILES Main.qml
        QML_FILES Model/HomeModel.qml
        QML_FILES View/HomeView.qml
        QML_FILES View/ListView.qml
        QML_FILES View/RootView.qml
        QML_FILES View/Button.qml
        SOURCES Model/MyTestModel.h Model/MyTestModel.cpp
        QML_FILES View/MyTestView.qml
        QML_FILES View/TextEdit.qml
        SOURCES Model/LogHandler.h Model/LogHandler.cpp
        SOURCES Model/DisplayMonitorInfo.h Model/DisplayMonitorInfo.cpp
        SOURCES Model/MonitorControl.h Model/MonitorControl.cpp
        QML_FILES View/MonitorControlView.qml
        QML_FILES View/DisplayMonitorInfoView.qml
)

if(WIN32)
    # 添加 WinRT 支持
    set(WINRT_INCLUDE_DIR "$ENV{WINDOWS_SDK_DIR}/Include/$ENV{WINDOWS_SDK_VERSION}/cppwinrt")

    if(EXISTS ${WINRT_INCLUDE_DIR})
        target_include_directories(appQtHelper PRIVATE ${WINRT_INCLUDE_DIR})
    else()
        message(FATAL_ERROR "WinRT headers not found at ${WINRT_INCLUDE_DIR}")
    endif()
    target_link_libraries(appQtHelper PRIVATE
        # -lruntimeobject
        -lwindowsapp
    )
    #include <physicalmonitorenumerationapi.h>
    #include <lowlevelmonitorconfigurationapi.h>
    target_link_libraries(appQtHelper PRIVATE dxva2)
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQtHelper PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQtHelper
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQtHelper PRIVATE Qt6::Quick)
target_link_libraries(appQtHelper PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appQtHelper
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
target_compile_definitions(appQtHelper PRIVATE __cpuidex=__dummy_cpuidex)
