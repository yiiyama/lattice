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
    nT = int(config['nT'])
    nX = int(config['nX'])
    if spatialDim == 0:
        field = ROOT.lattice.Particle(int(config['nT']), int(config['nX']), float(config['dt']))
    else:
        field = ROOT.lattice.Field(int(config['dim']), int(config['nT']), int(config['nX']))

    lagrangian = ROOT.lattice.getAction(config['lagrangian'], field)
    if 'parameters' in config:
        iP = 0
        for p in config['parameters'].split():
            lagrangian.setParameter(iP, float(p))
            iP += 1

    if 'BC' in config:
        if config['BC'] == 'Vanish':
            if spatialDim == 0:
                coord = field.getCoordObject(0)
                for iX in range(nX):
                    coord.moveTo(0, iX)
                    field.setBoundaryCondition(coord, 0.)
                    coord.moveTo(nT - 1, iX)
                    field.setBoundaryCondition(coord, 0.)

            else:
                for iD in range(1 + spatialDim):
                    coord = field.getCoordObject(0)
                    while coord.isValid():
                        if coord[iD] == 0 or coord[iD] == nX - 1:
                            field.setBoundaryCondition(coord, 0.)

                        coord.next()

        else:
            # form '(t,x,..):val '
            conds = config['BC'].split()
            coord = field.getCoordObject(0)
            for cond in conds:
                coordt = eval(cond.partition(':')[0])
                coord.moveTo(*coordt)
                if coord.isValid():
                    field.setBoundaryCondition(coord, float(cond.partition(':')[2]))
    
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
