#!/usr/bin/python
import pickle
import numpy as np
f = open('../dataset.pckl','rb');
X = pickle.load(f);
Y = pickle.load(f);
f.close();

matX = np.zeros((len(X),len(X[0])));
row_idx = 0;
for data in X:
  matX[row_idx,:] = np.asarray(data);
  row_idx += 1;
vecY = np.asarray(Y);
vecY = np.transpose(vecY);
