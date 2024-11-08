#!/usr/bin/python
import py_readdata as pr
X, Y = pr.my_read("dataset.txt");
import pickle
f = open('../dataset.pckl','wb');
pickle.dump(X,f);
pickle.dump(Y,f);
f.close();

