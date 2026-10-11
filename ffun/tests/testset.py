"""Choose the samples of a test set: the earliest and latest local version of each camera.

A test set file (e.g. testset.yaml) lists cameras by the model prefix of their firmware
file names (XT4 for XT4-0212-FWUP0024.DAT). The samples are chosen from the firmware
index at run time, so new firmware files are picked up without editing the set.
"""

import re
from pathlib import Path

import yaml

TESTS = Path(__file__).resolve().parent
VERSIONED = re.compile(r"^([A-Za-z0-9]+)-(\d{4})-")


def set_path(name: str) -> Path:
    """A set given by name (looked up next to this file) or by path."""
    p = Path(name)
    if p.exists():
        return p
    return TESTS / (name if name.endswith(".yaml") else f"{name}.yaml")


def load_set(name: str) -> dict:
    with open(set_path(name)) as f:
        return yaml.safe_load(f) or {}


def select(cameras, index_names) -> list[str]:
    """MODEL-VERSION names for the earliest and latest version of each camera.

    cameras: camera keys (model prefixes); index_names: firmware file names.
    Files without a MODEL-VVVV- prefix are ignored; a camera with one version
    contributes one sample, a camera without samples none."""
    versions = {}
    for name in index_names:
        m = VERSIONED.match(name)
        if m:
            versions.setdefault(m.group(1).upper(), set()).add(m.group(2))
    chosen = []
    for cam in cameras:
        v = sorted(versions.get(str(cam).upper(), ()))
        for ver in dict.fromkeys(v[:1] + v[-1:]):
            chosen.append(f"{str(cam).upper()}-{ver}")
    return chosen


def select_from_index(name: str) -> list[str]:
    """Samples of set `name` for the current firmware index (ffindex.yaml in fwdir)."""
    import sys
    sys.path.insert(0, str(TESTS.parents[1]))   # the ffun package
    from ffun import ffrepo
    with open(Path(ffrepo.get_repository_dir()) / "ffindex.yaml") as f:
        index = yaml.load(f, Loader=yaml.BaseLoader) or {}
    return select(load_set(name), index)
