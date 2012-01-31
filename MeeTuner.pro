# Add more folders to ship with the application, here
folder_01.source = qml/MeeTuner
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE4436BD8

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
if(isEmpty(MEEGO_VERSION_MAJOR)) {
        QT += multimedia
}

CONFIG += mobility
MOBILITY += multimedia

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components

include(3rdparty/3rdparty.pri)

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    analyzer/frequencyanalyzer.cpp \
    analyzer/noteanalyzer.cpp


# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

#CONFIG -= debug_and_release debug
#CONFIG += release

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

HEADERS += \
    analyzer/frequencyanalyzer_p.h \
    analyzer/frequencyanalyzer.h \
    analyzer/noteanalyzer_p.h \
    analyzer/noteanalyzer.h
