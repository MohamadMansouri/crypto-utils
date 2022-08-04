add_executable(test_fields test_fields.cpp)
add_executable(test_ecc test_ecc.cpp)
add_executable(test_dme test_dme.cpp)
add_executable(test_ot test_ot.cpp ../src/ot/ot.cpp ../src/ot/dot.cpp )

target_link_libraries(test_fields fields)
target_link_libraries(test_ecc ecc fields)
target_link_libraries(test_dme dme ecc fields)
target_link_libraries(test_ot dme ecc fields)


add_test(NAME Fields COMMAND test_fields)
add_test(NAME EllipticCurve COMMAND test_ecc)
add_test(NAME DualModeEnc COMMAND test_dme)
add_test(NAME OT COMMAND test_ot)