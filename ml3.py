import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

 
df = pd.read_csv('/home/lavesh/DSA/C/iris.csv')   

print("=" * 55)
print("         IRIS DATASET - OVERVIEW")
print("=" * 55)
print(f"Total Rows       : {df.shape[0]}")
print(f"Total Columns    : {df.shape[1]}")
print(f"\nSpecies Count (Original):\n{df['variety'].value_counts()}")

 
df_no_dup = df.drop_duplicates()
print(f"\nRows after removing duplicates : {df_no_dup.shape[0]}")
print(f"Species Count (After Removing Duplicates):\n{df_no_dup['variety'].value_counts()}")
print("=" * 55)


 

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))
fig.suptitle("Iris Dataset — Species Analysis", fontsize=16, fontweight='bold')

 
species_counts = df['variety'].value_counts()
colors_freq    = ['#E63946', '#2A9D8F', '#F4A261']

bars = ax1.bar(
    species_counts.index,
    species_counts.values,
    color     = colors_freq,
    edgecolor = 'black',
    linewidth = 0.8,
    width     = 0.5
)

for bar in bars:
    height = bar.get_height()
    ax1.text(
        bar.get_x() + bar.get_width() / 2,
        height + 0.5,
        str(int(height)),
        ha='center', va='bottom',
        fontsize=12, fontweight='bold'
    )

ax1.set_title('(a) Plot 1 : Frequency of Each Species', fontsize=12, pad=10)
ax1.set_xlabel('Species',           fontsize=12)
ax1.set_ylabel('Frequency (Count)', fontsize=12)
ax1.set_ylim(0, max(species_counts.values) + 8)
ax1.legend(bars, species_counts.index, title='Species', fontsize=10)
ax1.grid(axis='y', linestyle='--', alpha=0.6)
 
species_counts_nodup = df_no_dup['variety'].value_counts()

wedge_props = {'edgecolor': 'white', 'linewidth': 2}
explode     = (0.05, 0.05, 0.05)

wedges, texts, autotexts = ax2.pie(
    species_counts_nodup.values,
    labels     = species_counts_nodup.index,
    autopct    = '%1.1f%%',
    colors     = ['#E63946', '#2A9D8F', '#F4A261'],
    explode    = explode,
    startangle = 140,
    wedgeprops = wedge_props,
    shadow     = True
)

for autotext in autotexts:
    autotext.set_fontsize(11)
    autotext.set_fontweight('bold')
for text in texts:
    text.set_fontsize(11)

ax2.set_title(
    f'(a) Plot 2 : Pie Chart of Species\n(After Removing Duplicates — {df_no_dup.shape[0]} rows)',
    fontsize=12, pad=10
)

plt.tight_layout()
plt.savefig('iris_frequency_pie.png', dpi=150, bbox_inches='tight')
plt.show()
print("Figure 1 saved as 'iris_frequency_pie.png'")


 

fig2, ax3 = plt.subplots(figsize=(12, 6))

species_counts_all = df['variety'].value_counts()
x_positions        = np.arange(len(species_counts_all))
green_shades       = ['#1a7a1a', '#2ecc2e', '#57d657']

for i, (species, count) in enumerate(species_counts_all.items()):
    ax3.bar(
        x_positions[i],
        count,
        color     = green_shades[i],
        width     = 1,
        edgecolor = 'black',
        linewidth = 0.8,
        label     = species
    )
    ax3.text(
        x_positions[i],
        count + 0.5,
        str(count),
        ha='center', va='bottom',
        fontsize=12, fontweight='bold'
    )

ax3.set_title('(b) Bar Plot of Iris Dataset by Species\n(Colour=Green | Bar Width=1)',
              fontsize=14, fontweight='bold', pad=12)
ax3.set_xlabel('Species',           fontsize=13)
ax3.set_ylabel('Frequency (Count)', fontsize=13)
ax3.set_xticks(x_positions)
ax3.set_xticklabels(species_counts_all.index, fontsize=12)
ax3.set_ylim(0, max(species_counts_all.values) + 10)
ax3.legend(title='Species', title_fontsize=11, fontsize=10,
           loc='upper right', framealpha=0.9, edgecolor='grey')
ax3.grid(axis='y', linestyle='--', alpha=0.5)

plt.tight_layout()
plt.savefig('iris_barplot_green.png', dpi=150, bbox_inches='tight')
plt.show()
print("Figure 2 saved as 'iris_barplot_green.png'")