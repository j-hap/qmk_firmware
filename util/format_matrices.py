import re
import sys

# quick and dirty script to lay out keymap definitions in a keymap.c file
# to have the columns aligned


def format_block(block):
    if len(block) == 1:
        block = [",".join(block[0])]
        return block
    leading_whitespace = re.compile(r"\s*")
    indentation = min(len(leading_whitespace.match(line[0]).group(0)) for line in block)
    n_fields_max = max(len(line) for line in block)
    i_middle = n_fields_max / 2 - 0.5
    block = [[field.strip() for field in line] for line in block]
    field_width = (
        max(len(field) for line in block for field in line) + 2
    )  # +2 for comma and whitespace
    field_width = max(field_width, 10)
    for i_line, line in enumerate(block):
        n_fields_missing = n_fields_max - len(line)
        alignment = " " * (
            indentation + n_fields_missing // 2 * (field_width)
        )  # +2 for comma and whitespace
        for i_field, field in enumerate(line):
            # lr_index is negative if the entry is left from the middle, positive if it is right from the middle and 0 if it is the middle entry
            offset_from_middle = i_field - i_middle + n_fields_missing / 2
            if offset_from_middle < 0:
                block[i_line][i_field] = f"{field},".ljust(field_width)
            elif offset_from_middle > 0:
                block[i_line][i_field] = f"{field},".rjust(field_width)
            else:
                block[i_line][i_field] = f"{field},".center(field_width)
        block[i_line] = alignment + "".join(line)
    # the last line in a block must not have a trailing comma
    block[-1] = block[-1][:-1]
    return block


def split_on_top_level_comma(line):
    parens_level = 0
    first = 0
    pieces = []
    for i, c in enumerate(line):
        if c == "(":
            parens_level += 1
        elif c == ")":
            parens_level -= 1
        if c == "," and parens_level == 0:
            pieces.append(line[first:i])
            first = i + 1
    if first < len(line):
        pieces.append(line[first:])
    return pieces


def format_matrices(filename):
    block = []
    with open(filename, "rt") as f:
        for line in f:
            line = line.rstrip()  # removes trailing newline
            fields = split_on_top_level_comma(line)
            if len(fields) > 1 and not line.lstrip().startswith("//"):
                block.append(fields)
                continue
            # first line after a block, that is either a comment or does not have a top level comma
            if block:
                block = format_block(block)
                print("\n".join(block))
            print(line)
            block = []
        if block:
            block = format_block(block)
            print("\n".join(block))


if __name__ == "__main__":
    format_matrices(sys.argv[1])
