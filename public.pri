UI_DIR = ./temp/GeneratedFiles
RCC_DIR = ./temp/GeneratedFiles
MOC_DIR = ./temp/GeneratedFiles
INCLUDEPATH += ./temp/GeneratedFiles

win32{
    CONFIG -= flat
    OBJECTS_DIR = ./temp/$(Platform)/$(Configuration)
}

macx{
}
