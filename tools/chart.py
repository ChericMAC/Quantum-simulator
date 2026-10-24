import pandas as pd
import matplotlib.pyplot as plt

path = "results/"

df = pd.read_csv(path + "output.csv", header=None, names=['Bit', 'Occurrences'], dtype={'Bit': str})

x_labels = df['Bit'].astype(str)
y_values = df['Occurrences']

plt.figure(figsize=(9, 5), dpi=300)
plt.bar(x_labels, y_values, color='blue', width=0.55)

plt.title('Quantum simulation results')
plt.xlabel('Bit / State')
plt.ylabel('Number of occurrences')
plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.savefig(path + "chart.png")
plt.close()