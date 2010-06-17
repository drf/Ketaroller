add_executable(cmidiin cmidiin.cpp)
target_link_libraries(cmidiin rtmidi)

add_executable(midiout midiout.cpp)
target_link_libraries(midiout rtmidi)

add_executable(midiprobe midiprobe.cpp)
target_link_libraries(midiprobe rtmidi)

add_executable(qmidiin qmidiin.cpp)
target_link_libraries(qmidiin rtmidi)

add_executable(sysextest sysextest.cpp)
target_link_libraries(sysextest rtmidi)
