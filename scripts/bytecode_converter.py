from dataclasses import dataclass
import fire


BYTES = [
    "NXLL",
    "SETV",
    "SETC",
    "CADD",
    "CSUB",
    "CMUL",
    "CDIV",
    "IADD",
    "ISUB",
    "IMUL",
    "IDIV",
    "DADD",
    "DSUB",
    "DMUL",
    "DDIV",
    "CALL",
    "RTRN",
    "EXIT",
    "DREF",
]


@dataclass
class HumanReadableBytecode:
    code: str
    first_cell: str
    second_cell: str


@dataclass
class BytecodeString:
    code: str
    first_cell: str
    second_cell: str


@dataclass
class BytecodeBytes:
    code: bytearray
    first_cell: bytearray
    second_cell: bytearray


def cell_string_to_cell_list(cell: str):
    """Convert string representation of an eight character
    cell into a list of length 4 of ints

            '0000004f' -> [0, 0, 0, 79]
    """
    cell_list = []
    index = 0
    for x in range(4):
        y = 0
        section = ""
        while y < 2:
            section += cell[index]
            index += 1
            y += 1
        cell_list.append(int(section, 16))
    return cell_list


def human_readable_line_to_byte_string(line: str):
    """Convert human readable line into bytestring

        SETV 0000004f 12345678 -> 010000004f12345678

    """
    bytecode = HumanReadableBytecode(*line.split())
    return str(BYTES.index(bytecode.code)).zfill(2) + \
        bytecode.first_cell + bytecode.second_cell


def bytecode_string_to_bytearray(bytestring: str):
    """Convert bytecode into a bytearray object

        '010000004f12345678' -> bytearray(b'\x01\x00\x00\x00O\x124Vx')

    """
    bytecode = BytecodeString(
        bytestring[0:2],
        bytestring[2:10],
        bytestring[10:19]
    )

    new_bytearray = bytearray([int(bytecode.code)])
    new_bytearray.extend(cell_string_to_cell_list(bytecode.first_cell))
    new_bytearray.extend(cell_string_to_cell_list(bytecode.second_cell))
    return new_bytearray


def parse_human_readable_bytecode_file(path: str):
    """Open file and read by line, return bytestring line"""
    with open(path, "r") as file:
        for line in file.readlines():
            bytecode = human_readable_line_to_byte_string(line)
            yield bytecode


def parse_raw_bytecode_file(path: str):
    """Open file and return bit"""
    with open(path, "rb") as file:
        while 1:
            char = file.read(1)
            if not char:
                break
            yield char


def write_human_readable_file(path: str, lines):
    """Write lines to file"""
    with open(path, "w") as file:
        for line in lines:
            file.write(line)


def write_bytecode_string_file(path: str, lines):
    """Write lines as byte string (basically write_human_readable_file)"""
    with open(path, "w") as file:
        for line in lines:
            file.write(bytes(line, "UTF-8"))


def write_bytecode_bytearray_file(path: str, _bytearray):
    with open(path, "wb") as file:
        file.write(_bytearray)


def convert_human_readable_to_bytecode_file(input_path: str, output_path: str):
    """Open human readable file, convert to bytecode,
    then write as bytecode file"""
    parsed_file = parse_human_readable_bytecode_file(input_path)
    _bytes = bytearray()
    for parsed in parsed_file:
        _bytes.extend(bytecode_string_to_bytearray(parsed))
    write_bytecode_bytearray_file(output_path, _bytes)


def convert_bytecode_to_human_readable_file(input_path: str, output_path: str):
    """Open bytecode file, convert to human readable,
    then write as human readable file"""
    parsed_file = parse_raw_bytecode_file(input_path)
    write_human_readable_file(output_path, parsed_file)


class BytecodeConverter(object):
    """In the console, use these methods

    run './bytecode_converter.py command_name input_path output_path'

    """
    def human_readable_to_bytecode(self, input_path, output_path):
        convert_human_readable_to_bytecode_file(input_path, output_path)

    def bytecode_to_human_readable(self, input_path, output_path):
        convert_bytecode_to_human_readable_file(input_path, output_path)

    """Aliases to other commands"""
    def b2h(self, input_path, output_path):
        self.bytecode_to_human_readable(input_path, output_path)

    def h2b(self, input_path, output_path):
        self.human_readable_to_bytecode(input_path, output_path)


if __name__ == "__main__":
    fire.Fire(BytecodeConverter)
