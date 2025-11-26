#!/usr/bin/env python3
import csv
import io

import requests
import argparse

SPREADSHEET_ID = "1GxJ11mhCLwnj2ZY0ufKfn138SMgtq-6YtyhaEKHV1Fc"
SHEET_GID = "461174987"
REMOVE_COLUMNS = {
    "ID","syslog","auto_act.scr","PID", "IOP", "Image Sensor", "Notes"
}

def tsv_to_markdown(tsv : bytes) -> str:
    bio = io.BytesIO(tsv)
    reader = csv.reader(io.TextIOWrapper(bio, encoding="utf-8"), delimiter="\t")
    rows = list(reader)

    if not rows:
        return ""

    header = [col.strip() for col in rows[0]]
    body = rows[1:]

    keep_indices = [
        i for i, col in enumerate(header)
        if col not in REMOVE_COLUMNS
    ]

    filtered_header = [header[i] for i in keep_indices]
    bold_header = [f"**{col}**" for col in filtered_header]

    lines = []

    lines.append("| " + " | ".join(bold_header) + " |")
    lines.append("| " + " | ".join(["---"] * len(filtered_header)) + " |")

    for row in body:
        filtered_row = [row[i] if i < len(row) else "" for i in keep_indices]
        lines.append("| " + " | ".join(filtered_row) + " |")

    return "\n".join(lines)


def get_googlesheet():

    url = f"https://docs.google.com/spreadsheets/d/{SPREADSHEET_ID}/export"

    params = {
        "format": "tsv",
        "gid": SHEET_GID
    }

    r = requests.get(url, params=params)
    r.raise_for_status()
    return r.content

def parse_args() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Update firmware summary markdown for tb's wiki"
    )
    parser.add_argument(
        "-u",
        "--update",
        action="store_true",
        help="Download latest data from tb's google sheets",
    )

    parser.add_argument(
        "input",
        metavar="input.tsv",
        help="Input tab separated .tsv file"
    )

    parser.add_argument(
        "output",
        metavar="output.md",
        help="Output Markdown file"
    )

    return parser

if __name__ == "__main__":

    parser = parse_args()
    args = parser.parse_args()

    input_tsv = None
    output_md = None
    tsv = None

    if args.update:
        tsv = get_googlesheet()

    if tsv is not None:
        with open(args.input, "wb") as f:
            f.write(tsv)
    else:
        with open(args.input, "rb") as f:
            tsv = f.read()

    md = tsv_to_markdown(tsv)

    with open(args.output, "wt") as f:
        f.write(md)
