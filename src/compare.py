#!/usr/bin/env python3
import os
import sys

def compare(in1, in2, team):
	FOLDER = "tests"
	fpath1 = os.path.join(FOLDER, in1)
	fpath2 = os.path.join(FOLDER, in2)
	ranking1 = []
	ranking2 = []
	with open(fpath1) as file1:
		for line in file1:
			ranking1 += line.split()	
	with open(fpath2) as file2:
		for line in file2:
			ranking2 += line.split()

	for i in range(0,len(ranking1)):
 		ranking1[i] = float(ranking1[i])
	for i in range(0,len(ranking2)):
		ranking2[i] = float(ranking2[i])

	print(f"Team {team} ranking in file 1: {ranking1[int(team)-1]}")
	print(f"Team {team} ranking in file 2: {ranking2[int(team)-1]}")

def main():
	try:
		print("Input file 1: ")
		file1 = input()
		print("Input file 2: ")
		file2 = input()
		print("Team: ")
		team = input()
		compare(file1, file2, team)
	except ValueError:
		print("Team should be an integer")


while(True):
	main()




