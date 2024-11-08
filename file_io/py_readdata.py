
def my_read( filename ) :
  with open(filename,mode='r') as f: # f=open, f.close()
    lineno = 0;
    X = []; # An empty list for inputs;
    Y = []; # An empty list for classifications;
    for line in f: # f.readline()
      lineno += 1;
      if lineno % 3 is 1: # first of a group of three
        x_par = (); # Create an empty tuple (const)
        pars = line.split();
        for par in pars:
          pair = par.split("=");
          x_par += (float(pair[1]),); # Concatenate, not modify
        X += [x_par];
      elif lineno % 3 is 2: # second of a group of three
        pass; # do nothing
      else: # third of a group of three
        words = line.split();
        c_val = 0;
        if words[1][0] is 'S':
          c_val = 1; # stable
        else:
          c_val = -1;
        Y += [c_val];
  return X,Y;

