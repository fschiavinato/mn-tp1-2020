#!/usr/bin/env python3
import os
import statistics as st
import seaborn as sns
import matplotlib.pyplot as plt 

def compare(in1, in2, in3, team):
	FOLDER = "tests"
	fpath1 = os.path.join(FOLDER, in1)
	fpath2 = os.path.join(FOLDER, in2)
	fpath3 = os.path.join(FOLDER, in3)
	ratings1 = []
	ratings2 = []
	ratings3 = []
	with open(fpath1) as file1:
		for line in file1:
			ratings1 += line.split()	
	with open(fpath2) as file2:
		for line in file2:
			ratings2 += line.split()
	with open(fpath3) as file3:
		for line in file3:
			ratings3 += line.split()

	for i in range(0,len(ratings1)):
 		ratings1[i] = float(ratings1[i])
	for i in range(0,len(ratings2)):
		ratings2[i] = float(ratings2[i])
	for i in range(0,len(ratings3)):
		ratings3[i] = float(ratings3[i])

	diccRatings1 = {}
	diccRatings2 = {}
	diccRatings3 = {}

	for i in range(0,len(ratings1)):
		if ratings1[i] in diccRatings1:
			diccRatings1[ratings1[i]] += 1
		else:
			diccRatings1[ratings1[i]] = 1
		if ratings2[i] in diccRatings2: 
			diccRatings2[ratings2[i]] += 1
		else:
			diccRatings2[ratings2[i]] = 1
		if ratings3[i] in diccRatings3:
			diccRatings3[ratings3[i]] += 1
		else:
			diccRatings3[ratings3[i]] = 1

	ordRatings1 = []
	ordRatings2 = []
	ordRatings3 = []
	for rating in diccRatings1.keys():
		ordRatings1 = ordRatings1 + [rating]
	for rating in diccRatings2.keys():
		ordRatings2 = ordRatings2 + [rating]
	for rating in diccRatings3.keys():
		ordRatings3 = ordRatings3 + [rating]

	ordRatings1.sort(reverse=True)
	ordRatings2.sort(reverse=True)
	ordRatings3.sort(reverse=True)

	#Equipos con el mismo ránking tienen la misma posición
	print(f"Team {team} rating in file 1: {ratings1[team-1]}")
	print(f"Team {team} position in file 1: {ordRatings1.index(ratings1[team-1]) + 1} out of {len(ratings1)} teams")
	print(f"Team {team} rating in file 2: {ratings2[team-1]}")
	print(f"Team {team} position in file 2: {ordRatings2.index(ratings2[team-1]) + 1} out of {len(ratings2)} teams")
	print(f"Team {team} rating in file 3: {ratings3[team-1]}")
	print(f"Team {team} position in file 3: {ordRatings3.index(ratings3[team-1]) + 1} out of {len(ratings3)} teams")

	graph = sns.scatterplot(x=ratings2,y=ratings1)
	graph.set(xlabel="wp",ylabel="cmm")

	graph = sns.scatterplot(x=ratings3,y=ratings1)
	graph.set(xlabel="glicko",ylabel="cmm")

	graph = sns.scatterplot(x=ratings3,y=ratings2)
	graph.set(xlabel="glicko",ylabel="wp")

	plt.show()

def main():
	try:
		print("Input file 1: ")
		file1 = input()
		print("Input file 2: ")
		file2 = input()
		print("Input file 3: ")
		file3 = input()
		print("Team: ")
		team = int(input())
		compare(file1, file2, file3, team)
	except ValueError:
		print("Team should be an integer")

while(True):
	main()