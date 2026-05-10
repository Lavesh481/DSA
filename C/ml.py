import pandas as pd
import matplotlib.pyplot as plt

# 1. Read the iris.csv dataset
df = pd.read_csv('/home/lavesh/DSA/C/iris.csv')

# Define colours & markers per species
species_styles = {
    'Setosa'    : {'color': '#E63946', 'marker': 'o', 'label': 'Setosa'},
    'Versicolor': {'color': '#2A9D8F', 'marker': 's', 'label': 'Versicolor'},
    'Virginica' : {'color': '#F4A261', 'marker': '^', 'label': 'Virginica'},
}

fig, ax = plt.subplots(figsize=(9, 6))

# (a) Scatter plot: Sepal Length vs Sepal Width
# (b) Each species in a diffmatplotlib.pyplot as pltddddd  
for species, style in species_styles.items():
    subset = df[df['variety'] == species]
    ax.scatter(subset['sepal.length'], subset['sepal.width'],
               color=style['color'], marker=style['marker'],
               label=style['label'], s=90, edgecolors='white',
               linewidths=0.6, alpha=0.90)

ax.set_xlabel('Sepal Length (cm)', fontsize=13)
ax.set_ylabel('Sepal Width (cm)',  fontsize=13)
ax.set_title('Iris Dataset — Sepal Length vs Sepal Width\n(Coloured by Species)',
             fontsize=15, fontweight='bold')
ax.legend(title='Species', fontsize=10)

# (c) Grid: colour=blue | linestyle=dashed | linewidth=1 pt
ax.grid(True, color='blue', linestyle='--', linewidth=1)
ax.set_axisbelow(True)

plt.tight_layout()
plt.savefig('iris_scatter_plot.png', dpi=150, bbox_inches='tight')
plt.show()