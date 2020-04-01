#!/usr/bin/env python3

import pandas as pd
import numpy as np
import scipy.stats
import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import axes3d, Axes3D
import pylab as pl
plt.style.use('sig-alternate.mplrc')


# plt.style.use('grcon.mplrc')

my_colors = plt.rcParams['axes.prop_cycle'].by_key()['color']


def conf_int(data, confidence=0.95):
    a = 1.0 * np.array(data)
    n = len(a)
    m, se = np.mean(a), scipy.stats.sem(a)
    if (n < 2) or (se == 0):
        return np.nan
    h = se * scipy.stats.t.ppf((1 + confidence) / 2., n - 1)
    return h


################################################################
## Line Plot RT-Prio (n, n) scaling
################################################################
d = (pd.read_csv('../perf-data/1_2_3PU-samples=100000000.csv'))
#d = (pd.read_csv('../perf-data/2_3PU-samples=100000000.csv'))
#d = (pd.read_csv('../perf-data/1PU-samples=100000000.csv'))

#print(d)
d.set_index("pipes", inplace=True)


# dr = d.drop_duplicates(subset='run')


# Create the violineplot

print('1x1:', d.loc[1]['time'].mean())
print('1x1:', d.loc[1]['time'].median())
print('2x2:', d.loc[2]['time'].mean())
print('3x3:', d.loc[3]['time'].mean())
print('4x4:', d.loc[4]['time'].mean())
print('5x5:', d.loc[5]['time'].mean())
print('6x6:', d.loc[6]['time'].mean())
print('7x7:', d.loc[7]['time'].mean())
print('8x8:', d.loc[8]['time'].mean())
print('9x9:', d.loc[9]['time'].mean())
print('10x10:', d.loc[10]['time'].mean())
print('10x10:', d.loc[10]['time'].median())

pos = ['10x10', '2x2', 3, 4, 5, 6, 7, 8, 9, 10]
fig, axes = plt.subplots(1, 1)

test = [d.loc[1]['time'], d.loc[2]['time'], d.loc[3]['time'], d.loc[4]['time'], d.loc[5]['time'],
        d.loc[6]['time'], d.loc[7]['time'], d.loc[8]['time'], d.loc[9]['time'], d.loc[10]['time']]


axes.boxplot(test, showfliers=False, notch=True, showmeans=True)
axes.set_title('Custom violinplot 1')

# axes.set_xlabel('Number of Runs')
axes.set_xlabel('Run')
axes.set_ylabel('Time (in millisekunden)')

fig.suptitle("Violin Plot")
fig.subplots_adjust(hspace=0.4)
plt.show()

# fig.savefig('dur-violin.pdf')
