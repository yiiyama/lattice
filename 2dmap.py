import sys
sys.argv = ['', '-b']
import ROOT

canvas = ROOT.TCanvas('c1', 'c1')
source = ROOT.TFile('/tmp/yiiyama/Quartic.root')
tree = source.Get('config')

values = ROOT.TProfile2D('values', 'field values;X;T', 10, 0., 10., 10, 0., 10.)

for iT in range(10):
    for iX in range(10):
        name = '%d_%d' % (iT, iX)
        tree.Draw(name + ':%d:%d>>+values' % (iT, iX), '', 'goff')

values.Draw('COLZ')
canvas.Print('2dmap.pdf')
