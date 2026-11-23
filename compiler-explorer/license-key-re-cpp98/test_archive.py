#!/usr/bin/env python3
"""Compile each teaching example as strict C++98 and check both branches."""

import pathlib
import subprocess
import tempfile

ROOT = pathlib.Path(__file__).resolve().parent
CASES = [
    ("01_literal.cpp", "ORBIT-2026", "WRONG"),
    ("02_format.cpp", "ABCD-1234", "ABC-1234"),
    ("03_check_digit.cpp", "123455", "123456"),
    ("04_xor.cpp", "ORBIT", "WRONG"),
    ("05_name_serial.cpp", "bob 2180", "bob 2181"),
    ("06_fnv1a.cpp", "abc 1A47E90B", "abc 00000000"),
    ("07_toy_signature.cpp", "42 3065", "42 3064"),
    ("08_casefold.cpp", "orbit-2026", "wrong"),
    ("09_segments.cpp", "LIC-ORBIT-END", "LIC-ORBIT-NO"),
    ("10_poly_hash.cpp", "bob 97717", "bob 97718"),
    ("11_mirrored_digits.cpp", "123456", "123457"),
    ("12_base36.cpp", "1Z 71", "1Z 70"),
    ("13_lookup_table.cpp", "ABCD", "ABCF"),
    ("14_crc16.cpp", "ORBIT 2326", "ORBIT 0000"),
    ("15_machine_binding.cpp", "bob PC42 9684", "bob PC42 9685"),
    ("16_expiry.cpp", "20270101 20261123", "20250101 20261123"),
    ("17_feature_flags.cpp", "A5", "20"),
    ("18_group_relation.cpp", "1234-8649", "1234-8648"),
    ("19_rotating_xor.cpp", "bob E7", "bob E6"),
    ("20_tea_token.cpp", "ORBIT 7E9C999771CA4174", "ORBIT 0000000000000000"),
]

with tempfile.TemporaryDirectory() as temp:
    for source, good, bad in CASES:
        binary = pathlib.Path(temp) / source.replace(".cpp", "")
        subprocess.run(
            ["g++", "-std=c++98", "-pedantic-errors", "-Wall", "-Wextra",
             str(ROOT / source), "-o", str(binary)],
            check=True,
        )
        for value, expected in ((good, "VALID"), (bad, "INVALID")):
            result = subprocess.run(
                [str(binary), *value.split()], capture_output=True, text=True,
                check=True,
            )
            assert result.stdout.strip() == expected, (source, value, result.stdout)
        print("PASS", source)
