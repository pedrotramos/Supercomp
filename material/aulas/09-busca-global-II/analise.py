import pandas as pd
import matplotlib.pyplot as plt
import subprocess
import time


def rodaExecutavel(executavel, arquivo_in):
    with open(f"{arquivo_in}.txt") as f:
        start = time.perf_counter()
        proc = subprocess.run(
            [f"./{executavel}"], input=f.read(), text=True, capture_output=True
        )
        end = time.perf_counter()
        tempo = end - start

    return (proc.stdout, tempo)


inputFiles = ["in1", "in2", "in3", "in4", "in5"]
execFiles = ["mais-leve", "mais-caro", "aleatorizado", "busca-local", "busca-global"]
dadosTempo = {}

dadosTempo["InputSize"] = []

for file in execFiles:
    dadosTempo[file] = []

# Tamanhos das entradas
for file in inputFiles:
    with open(f"{file}.txt") as f:
        dadosTempo["InputSize"].append(int(f.readline().split()[0]))

for executavel in execFiles:
    for file in inputFiles:
        stdout, tempo = rodaExecutavel(executavel, file)
        dadosTempo[executavel].append(tempo)

df = pd.DataFrame(data=dadosTempo)
df.sort_values(by="InputSize", inplace=True)
df.reset_index(drop=True, inplace=True)

print(df)