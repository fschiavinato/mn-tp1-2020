import numpy as np
import pandas as pd 
import re
import os
import subprocess

def main(file_path):
    file = open(file_path)
    T, P = map(int, file.readline().split(' '))
    c = 2*np.eye(int(T))
    res = np.array(T)

    b = [1 for _ in range(T)]
    for line in file:
        e1, g1, e2, g2 = map(int, line.split()[1:5])
        c[e1-1][e2-1] -= 1
        c[e2-1][e1-1] -= 1
        c[e1-1][e1-1] += 1
        c[e2-1][e2-1] += 1
        if g1 > g2:
            b[e1-1] += 0.5
            b[e2-1] -= 0.5
        else:
            b[e2-1] += 0.5
            b[e1-1] -= 0.5
    return np.linalg.solve(c, b)

TESTS_DIR = '../tests'
BIN = '../tp'
def results():
    
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
        if f'{test}.out' not in test_files:
            print(f'generating {test}.out')
            subprocess.run([BIN, test_in, test_out, '0'])
        if f'{test}.expected' not in test_files:
            print(f'generating {test}.expected')
            r_ref[test] = main(test_in)
            with open(test_expected, 'w') as expected_file:
                expected_file.write('\n'.join(str(value) for value in r_ref[test]))
        with open(test_out) as res:
                r[test] = [float(line.strip()) for line in res if len(line.strip())>0]
        with open(test_expected) as res:
                r_ref[test] = [float(line.strip()) for line in res if len(line.strip())>0]
    return r, r_ref


def test_generator(name, victorias):
    matches = []
    T = len(victorias)
    for i, row in enumerate(victorias):
        for j, aij in enumerate(row):
            matches += aij*((i, j),)
    test_generator_matches(name, matches, T)
    

def test_generator_matches(name, matches, T):
    matches_output = []
    for (i, j) in matches:
        matches_output += [f'1 {i+1} 1 {j+1} 0']
    P = len(matches)
    file_path = f'{TESTS_DIR}/{name}.in'
    dir_path = os.path.dirname(file_path)
    try:
        os.makedirs(dir_path)
    except:
        pass
    with open(file_path, 'w') as file:
        file.write('\n'.join([f'{T} {P}', *matches_output]))
    try:
        os.remove(f'{TESTS_DIR}/{name}.out')
    except:
        pass
    try:
        os.remove(f'{TESTS_DIR}/{name}.expected')
    except:
        pass