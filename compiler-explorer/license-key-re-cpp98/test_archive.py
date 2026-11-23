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
