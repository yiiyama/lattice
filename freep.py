import sys
sys.argv = ['', '-b']
import ROOT

canvas = ROOT.TCanvas('c1', 'c1')
source = ROOT.TFile('/tmp/yiiyama/HarmonicOscillator.root')
tree = source.Get('config')

pos = ROOT.TGraphErrors(20)

for iT in range(20):
    name = str(iT) + '_0'
    tree.Draw(name + '>>hist', '', 'goff')
    hist = ROOT.gDirectory.Get('hist')
    pos.SetPoint(iT, iT, hist.GetMean())
    pos.SetPointError(iT, 0., hist.GetRMS())

pos.SetMarkerStyle(8)
pos.Draw('APE')
canvas.Print('freep.pdf')
