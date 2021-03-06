unix:exec = $$PWD/SnakeServer/serverProtocolTests/build/release/serverTests
win32:exec = $$PWD/SnakeServer/serverProtocolTests/build/release/serverTests.exe
QT_DIR = $$[QT_HOST_BINS]

win32:QMAKE_BIN = $$QT_DIR/qmake.exe
contains(QMAKE_HOST.os, Linux):{
    QMAKE_BIN = $$QT_DIR/qmake
}



deployTest.commands = cqtdeployer -bin $$exec clear -qmake $$QMAKE_BIN -targetDir $$PWD/deployTests -libDir $$PWD -recursiveDepth 5

test.depends = deployTest
unix:test.commands = $$PWD/deployTests/serverTests.sh
win32:test.commands = $$PWD/deployTests/serverTests.exe

QMAKE_EXTRA_TARGETS += \
    deployTest \
    test

