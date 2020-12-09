import bytecode_converter


def test_cell_string_to_cell_list():
    byte_s_to_l = bytecode_converter.cell_string_to_cell_list
    assert byte_s_to_l("ff000000") == [255, 0, 0, 0]
    assert byte_s_to_l("0100000f") == [1, 0, 0, 15]
    assert byte_s_to_l("01240606") == [1, 36, 6, 6]


def test_human_readable_line_to_byte_string():
    byte_h_b_string = bytecode_converter.human_readable_line_to_byte_string
    assert byte_h_b_string("SETV 0000004f 12345678") == "010000004f12345678"
    assert byte_h_b_string("NXLL 00000022 23232323") == "000000002223232323"
    assert byte_h_b_string("CADD 00000010 33323332") == "030000001033323332"


def test_bytecode_string_to_bytearray():
    byte_s_to_b_array = bytecode_converter.bytecode_string_to_bytearray
    assert byte_s_to_b_array("010000004f12345678") == \
        bytearray(b'\x01\x00\x00\x00O\x124Vx')
    assert byte_s_to_b_array("000000002223232323") == \
        bytearray(b'\x00\x00\x00\x00"####')
    assert byte_s_to_b_array("030000001033323332") == \
        bytearray(b'\x03\x00\x00\x00\x103232')
