QT += widgets
QT += core
CONFIG += c++11

HEADERS += \
    ui_window.h \
    ui_tree_node.h \
    ui_tree_edge.h \
    tree_node.h \
    binary_search_tree.h

SOURCES += \
    ui_window.cpp \
    main.cpp \
    ui_tree_node.cpp \
    ui_tree_edge.cpp \
    binary_search_tree.cpp

RESOURCES += \
    Resource.qrc