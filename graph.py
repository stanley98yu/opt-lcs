""" Python module for graphing performance.
    Note that this program works by reading in stdout from the C executable, so
    the program must be modified to only print the time for it to work.
    To run this script, compile the code version that you want to measure and
    run 'python3 graph.py'.
"""
import io
import subprocess

from tqdm import tqdm
import matplotlib.pyplot as plt
import numpy as np

DATA = "sample_data/dna1"
RUNS = 10000

def avg(data):
    return sum(data) / RUNS

def graph(data):
    n, bins, patches = plt.hist(x=data, bins='auto', color='#0504aa',
                                alpha=0.7, rwidth=0.85)
    plt.grid(axis='y', alpha=0.75)
    plt.xlabel('Ticks')
    plt.ylabel('Frequency')
    plt.title(f"Ticks Histogram on {DATA}")
    maxfreq = n.max()
    # Set a clean upper y-axis limit.
    plt.ylim(ymax=np.ceil(maxfreq / 10) * 10 if maxfreq % 10 else maxfreq + 10)
    print(f"Avg: {avg(data)}")
    plt.savefig("graph.png")

if __name__ == "__main__":
    results = []
    for i in tqdm(range(RUNS)):
        proc = subprocess.Popen(["./a.out", DATA+"-1.txt", DATA+"-2.txt"],
                                stdout=subprocess.PIPE)
        for line in io.TextIOWrapper(proc.stdout, encoding="utf-8"):
            results.append(int(line))
    graph(results)
