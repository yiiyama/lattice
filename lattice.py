#!/usr/bin/env python

import sys
import os
import re

try:
    configName = sys.argv[1]
except IndexError:
    print 'Usage: lattice.py config'
    sys.exit(1)

config = {}
try:
    with open(configName) as configFile:
        for line in configFile:
            line = line.strip()
            if line[0] == '#': continue
            config[line.partition(' ')[0]] = line.partition(' ')[2]

except IOError:
    print 'Could not open configuration file', configName
    sys.exit(1)

sys.argv = ['', '-b']
import ROOT
ROOT.gStyle.SetOptStat(0)

ROOT.gSystem.Load('libLattice.so')
ROOT.gSystem.Load('libAction.so')

try:
    spatialDim = int(config['dim'])
    if spatialDim == 0:
        physObj = ROOT.lattice.Particle(int(config['nT']), int(config['nX']), float(config['dt']))
    else:
        physObj = ROOT.lattice.Field(int(config['dim']), int(config['nT']), int(config['nX']))
    
    lagrangian = ROOT.lattice.getAction(config['lagrangian'], physObj)
    if 'parameters' in config:
        iP = 0
        for p in config['parameters'].split():
            lagrangian.setParameter(iP, float(p))
            iP += 1
    
    main = ROOT.lattice.LatticeSimulation(lagrangian)

    if 'nSweeps' in config:
        main.setNSweeps(int(config['nSweeps']))
    if 'thermalization' in config:
        main.setThermalizationWait(int(config['thermalization']))
    if 'fluctuation' in config:
        main.setFluctuationSize(float(config['fluctuation']))
    if 'output' in config:
        main.setOutputName(config['output'])
    if 'fillper' in config:
        main.setFillInterval(int(config['fillper']))

except KeyError:
    print 'Configuration error:'
    print config
    sys.exit(1)

main.run()
