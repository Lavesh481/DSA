import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# ── 1. Read the iris.csv dataset ───────────────────────────────────────────────
df = pd.read_csv('/home/lavesh/DSA/C/iris.csv')   # ← Change path if needed

print("=" * 50)
print("       IRIS DATASET - PETAL WIDTH ANALYSIS")
print("=" * 50)
print(df[['petal.width']].describe())

# ── (b) Skewness Calculation ───────────────────────────────────────────────────
skewness = df['petal.width'].skew()
print(f"\nSkewness Value : {skewness:.4f}")

if skewness > 0.5:
    skew_label = "Positively Skewed (Right-Skewed)"
    skew_desc  = "Tail is on the RIGHT side"
elif skewness < -0.5:
    skew_label = "Negatively Skewed (Left-Skewed)"
    skew_desc  = "Tail is on the LEFT side"
else:
    skew_label = "Approximately Symmetric"
    skew_desc  = "Data is evenly distributed"

print(f"Distribution   : {skew_label}")
print(f"Interpretation : {skew_desc}")
print("=" * 50)

# ── Figure Layout: 1 row, 2 columns ───────────────────────────────────────────
fig, axes = plt.subplots(1, 2, figsize=(14, 6))
fig.suptitle("Iris Dataset — Petal Width Analysis", fontsize=16, fontweight='bold')

# ══════════════════════════════════════════════════════════════════════════
# Plot 1 — (a) Horizontal Boxplot + (b) Skewness Info
# ══════════════════════════════════════════════════════════════════════════
ax1 = axes[0]

# (a) Horizontal Boxplot
sns.boxplot(
    x          = df['petal.width'],
    ax         = ax1,
    orient     = 'h',
    color      = '#4C72B0',
    width      = 0.4,
    flierprops = dict(marker='o', markerfacecolor='red',
                      markersize=7, markeredgecolor='darkred')
)

# Strip plot — individual data points
sns.stripplot(
    x      = df['petal.width'],
    ax     = ax1,
    orient = 'h',
    color  = 'orange',
    alpha  = 0.5,
    size   = 4,
    jitter = True
)

# Annotate Q1, Median, Mean, Q3 as vertical dashed lines
q1  = df['petal.width'].quantile(0.25)
med = df['petal.width'].median()
q3  = df['petal.width'].quantile(0.75)
mn  = df['petal.width'].mean()

for val, lbl, col in [
    (q1,  f'Q1={q1}',       'green'),
    (med, f'Median={med}',  'blue'),
    (q3,  f'Q3={q3}',       'purple'),
    (mn,  f'Mean={mn:.2f}', 'red')
]:
    ax1.axvline(val, color=col, linestyle='--', linewidth=1.3, alpha=0.85)
    ax1.text(val, 0.38, lbl, color=col, fontsize=8.5, ha='center',
             bbox=dict(boxstyle='round,pad=0.2', facecolor='white', alpha=0.8))

ax1.set_title(
    f'(a) Horizontal Boxplot — Petal Width\n'
    f'(b) Distribution : {skew_label}\n'
    f'     Skewness = {skewness:.4f}  →  {skew_desc}',
    fontsize=10.5, pad=12
)
ax1.set_xlabel('Petal Width (cm)', fontsize=12)
ax1.set_yticks([])

# ══════════════════════════════════════════════════════════════════════════
# Plot 2 — (c) Seaborn Detail: Violin + Box + Swarm by Species
# ══════════════════════════════════════════════════════════════════════════
ax2 = axes[1]

palette = {'Setosa': '#E63946', 'Versicolor': '#2A9D8F', 'Virginica': '#F4A261'}

# Violin plot — shows distribution shape (KDE)
sns.violinplot(
    data    = df,
    x       = 'petal.width',
    y       = 'variety',
    hue     = 'variety',
    ax      = ax2,
    orient  = 'h',
    palette = palette,
    alpha   = 0.5,
    inner   = None,
    legend  = False
)

# Boxplot on top of violin
sns.boxplot(
    data    = df,
    x       = 'petal.width',
    y       = 'variety',
    hue     = 'variety',
    ax      = ax2,
    orient  = 'h',
    palette = palette,
    width   = 0.25,
    legend  = False,
    flierprops = dict(marker='D', markerfacecolor='black', markersize=5)
)

# Swarmplot — individual data points per species
sns.swarmplot(
    data    = df,
    x       = 'petal.width',
    y       = 'variety',
    ax      = ax2,
    orient  = 'h',
    color   = 'black',
    alpha   = 0.5,
    size    = 3
)

ax2.set_title(
    '(c) Seaborn Detail — Petal Width by Species\n'
    '[ Violin Plot + Box Plot + Swarm Plot ]',
    fontsize=10.5, pad=12
)
ax2.set_xlabel('Petal Width (cm)', fontsize=12)
ax2.set_ylabel('Species',          fontsize=12)

# ── Save & Show ────────────────────────────────────────────────────────────────
plt.tight_layout()
plt.savefig('iris_boxplot.png', dpi=150, bbox_inches='tight')
plt.show()
print("\nPlot saved as 'iris_boxplot.png'")