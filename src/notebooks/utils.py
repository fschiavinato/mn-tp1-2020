import numpy as np
import sympy as sp
import pandas as pd 
import re
import os
import subprocess
TESTS_DIR = '../tests'
BIN = '../tp'


# DECORATORS

def save(f):

    def _f(ipath, opath):
        res = f(ipath)
        with open(opath, 'w') as file:
            file.write('\n'.join(str(value) for value in res))
    _f.no_save = f
    return _f


# ALGORITHMS

@save
def reference(ipath):
    file = open(ipath)
    T, P = map(int, file.readline().split(' '))
    c = 2*np.eye(int(T))
    res = np.array(T)
    b = [1 for _ in range(T)]
    for line in file:
        e1, g1, e2, g2 = map(int, line.split()[1:5])
        c[e1-1, e2-1] -= 1
        c[e2-1, e1-1] -= 1
        c[e1-1, e1-1] += 1
        c[e2-1, e2-1] += 1
        if g1 > g2:
            b[e1-1] += 0.5
            b[e2-1] -= 0.5
        else:
            b[e2-1] += 0.5
            b[e1-1] -= 0.5
    return np.linalg.solve(c, b)

def own(ipath, opath):
    subprocess.run([BIN, ipath, opath, '0'])

@save
def reference_no_matches(ipath):
    file = open(ipath)
    T = int(file.readline())
    c = 2*np.eye(int(T))
    res = np.array(T)
    b = [1 for _ in range(T)]
    for i, line in enumerate(file):
        for j, wij in enumerate(map(int, line.split())):
            c[i][j] -= wij
            c[j][i] -= wij
            c[i][i] += wij
            c[j][j] += wij
            b[i] += 0.5*wij
            b[j] -= 0.5*wij
    return np.linalg.solve(c, b)

# API

def run_cached(ipath, opath, f, cached):
    if opath not in cached: 
        print(f'generating {opath}')
        f(ipath, opath)
    with open(opath) as res:
        return [float(line.strip()) for line in res if len(line.strip())>0]

def results(with_matches=True):
    test_files = [os.path.join(root, name)
             for root, dirs, files in os.walk(TESTS_DIR)
             for name in files
             if name.endswith((".in", ".out", ".expected"))]
    tests = [re.match(r"(.*)\.in$", file)[1] for file in test_files if re.match(r".*\.in$", file) is not None]
    r = {}
    r_ref = {}
    for test in tests:
        test_in = f'{test}.in'
        test_out = f'{test}.out'
        test_expected = f'{test}.expected'
        r[test] = run_cached(test_in, test_out, own, test_files)
        if with_matches:
            r_ref[test] = run_cached(test_in, test_expected, reference, test_files)
        else:
            r_ref[test] = run_cached(test_in, test_expected, reference_no_matches, test_files)
    return r, r_ref

def test_generator(name, victorias, with_matches=True):
    matches = []
    T = len(victorias)
    for i, row in enumerate(victorias):
        for j, aij in enumerate(row):
            matches += aij*((i, j),)
    if with_matches:
        test_generator_matches(name, matches, T)
    else:
        _test_generate_from_lines([
            f'{T}',
            *[' '.join(str(entry) for entry in row) for row in victorias]],
            name)
    

def test_generator_matches(name, matches, T):
    matches_output = []
    for (i, j) in matches:
        matches_output += [f'1 {i+1} 1 {j+1} 0']
    P = len(matches)
    _test_generate_from_lines([f'{T} {P}', *matches_output], name)

def _test_generate_from_lines(lines, name):
    file_path = f'{TESTS_DIR}/{name}.in'
    dir_path = os.path.dirname(file_path)
    try:
        os.makedirs(dir_path)
    except:
        pass
    with open(file_path, 'w') as file:
        file.write('\n'.join(lines))
    try:
        os.remove(f'{TESTS_DIR}/{name}.out')
    except:
        pass
    try:
        os.remove(f'{TESTS_DIR}/{name}.expected')
    except:
        pass