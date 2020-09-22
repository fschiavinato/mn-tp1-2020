#!/usr/bin/env python3
import os
import sys

def compare(in1, in2, team):
	FOLDER = "tests"
	fpath1 = os.path.join(FOLDER, in1)
	fpath2 = os.path.join(FOLDER, in2)
	ratings1 = []
	ratings2 = []
	with open(fpath1) as file1:
		for line in file1:
			ratings1 += line.split()	
	with open(fpath2) as file2:
		for line in file2:
			ratings2 += line.split()

	for i in range(0,len(ratings1)):
 		ratings1[i] = float(ratings1[i])
	for i in range(0,len(ratings2)):
		ratings2[i] = float(ratings2[i])

	diccRatings1 = {}
	diccRatings2 = {}
	for i in range(0,len(ratings1)):
		if ratings1[i] in diccRatings1:
			diccRatings1[ratings1[i]] += 1
		else:
			diccRatings1[ratings1[i]] = 1
		if ratings2[i] in diccRatings2: 
			diccRatings2[ratings2[i]] += 1
		else:
			diccRatings2[ratings2[i]] = 1

	ordRatings1 = []
	ordRatings2 = []
	for rating in diccRatings1.keys():
		ordRatings1 = ordRatings1 + [rating]
	for rating in diccRatings2.keys():
		ordRatings2 = ordRatings2 + [rating]

	ordRatings1.sort(reverse=True)
	ordRatings2.sort(reverse=True)

	print(f"Team {team} rating in file 1: {ratings1[team-1]}")
	print(f"Team {team} position in file 1: {ordRatings1.index(ratings1[team-1]) + 1} out of {len(ratings1)} teams")
	print(f"Team {team} rating in file 2: {ratings2[team-1]}")
	print(f"Team {team} position in file 2: {ordRatings2.index(ratings2[team-1]) + 1} out of {len(ratings2)} teams")

def main():
	try:
		print("Input file 1: ")
		file1 = input()
		print("Input file 2: ")
		file2 = input()
		print("Team: ")
		team = int(input())
		compare(file1, file2, team)
	except ValueError:
		print("Team should be an integer")


while(True):
	main()




