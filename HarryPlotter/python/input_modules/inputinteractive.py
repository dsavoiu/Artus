# -*- coding: utf-8 -*-

"""
"""

import logging
import Artus.Utility.logger as logger
log = logging.getLogger(__name__)

import array
import hashlib
import ROOT
import sys

import Artus.HarryPlotter.inputbase as inputbase
import Artus.HarryPlotter.utility.roottools as roottools
import Artus.Utility.progressiterator as pi


class InputInteractive(inputbase.InputBase):
	def __init__(self):
		super(InputInteractive, self).__init__()
	
	def modify_argument_parser(self, parser, args):
		super(InputInteractive, self).modify_argument_parser(parser, args)
		
		self.input_options.add_argument("--x-errors", type=str, nargs="+",
		                                help="x-error(s)")
		self.input_options.add_argument("--y-errors", type=str, nargs="+",
		                                help="y-error(s)")
		self.input_options.add_argument("--z-errors", type=str, nargs="+",
		                                help="z-error(s)")
	
	def prepare_args(self, parser, plotData):
		super(InputInteractive, self).prepare_args(parser, plotData)
		
		self.prepare_list_args(plotData, ["nicks", "x_expressions", "y_expressions", "z_expressions", "x_bins", "y_bins", "z_bins", "scale_factors", "x_errors", "y_errors", "z_errors"])
		
		def secure_float_conversion(input_string):
			try:
				return float(input_string)
			except:
				return input_string
		
		for key in ["x_bins", "y_bins", "z_bins"]:
			for index, binning in enumerate(plotData.plotdict[key]):	
				if (not binning is None) and (len(binning) > 1):
					plotData.plotdict[key][index] = [float(bin_edge) for bin_edge in binning]
		
		# parse values/errors to plot
		values_keys = ["x_expressions", "y_expressions", "z_expressions"]
		errors_keys = ["x_errors", "y_errors", "z_errors"]
		for key in values_keys + errors_keys:
			if plotData.plotdict[key] != None:
				plotData.plotdict[key] = [[secure_float_conversion(value) for value in (values.split() if values != None else [])] for values in plotData.plotdict[key]]
		
		# set default errors to 0.0
		for index in xrange(len(plotData.plotdict["nicks"])):
			for values_key, errors_key in zip(values_keys, errors_keys):
				if len(plotData.plotdict[errors_key][index]) == 0:
					plotData.plotdict[errors_key][index] = len(plotData.plotdict[values_key][index]) * [0.0]
		
		# check that x/y/z values/errors for one plot have the same size
		for index in xrange(len(plotData.plotdict["nicks"])):
			n_values_per_plot = []
			for key in values_keys + errors_keys:
				if len(plotData.plotdict[key][index]) > 0:
					n_values_per_plot.append(len(plotData.plotdict[key][index]))
			assert(len(set(n_values_per_plot)) == 1)
		
		inputbase.InputBase.prepare_nicks(plotData)
	
	def run(self, plotData):
		
		for index, (
				nick,
				x_bins, x_values, x_errors,
				y_bins, y_values, y_errors,
				z_bins, z_values, z_errors,
		) in enumerate(pi.ProgressIterator(zip(*[plotData.plotdict[key] for key in [
				"nicks",
				"x_bins", "x_expressions", "x_errors",
				"y_bins", "y_expressions", "y_errors",
				"z_bins", "z_expressions", "z_errors",
		]]), description="Reading inputs")):
			
			# prepare unique name
			name_hash = hashlib.md5("_".join([str(item) for item in [nick, x_bins, x_values, x_errors, y_bins, y_values, y_errors, z_bins, z_values, z_errors]])).hexdigest()
			
			if x_bins is None:
				
				# Functions
				if len(y_values) == 0:
					expression = " ".join(x_values)
					formula = ROOT.TFormula("formula_"+name_hash, expression)
					function_class = None
					if formula.GetNdim() == 1:
						function_class = ROOT.TF1
					elif formula.GetNdim() == 2:
						function_class = ROOT.TF2
					else:
						function_class = ROOT.TF3
					plotData.plotdict.setdefault("root_objects", {})[nick] = function_class("function_"+name_hash, expression)
				
				# Graphs
				else:
					if len(z_values) == 0:
						plotData.plotdict.setdefault("root_objects", {})[nick] = ROOT.TGraphErrors(
								len(x_values),
								array.array("d", x_values), array.array("d", y_values),
								array.array("d", x_errors), array.array("d", y_errors)
						)
					else:
						plotData.plotdict.setdefault("root_objects", {})[nick] = ROOT.TGraph2DErrors(
								len(x_values),
								array.array("d", x_values), array.array("d", y_values), array.array("d", z_values),
								array.array("d", x_errors), array.array("d", y_errors), array.array("d", z_errors)
						)
					plotData.plotdict["root_objects"][nick].SetName("graph_"+name_hash)
					plotData.plotdict["root_objects"][nick].SetTitle("")
			
			# Histograms
			else:
				root_histogram = roottools.RootTools.create_root_histogram(
						x_bins=x_bins,
						y_bins=y_bins,
						z_bins=z_bins,
						profile_histogram=False,
						name="histogram_"+name_hash
				)
				
				weights = array.array("d", [1.0]*len(x_values))
				if root_histogram.GetDimension() == 1:
					if len(y_values) == 0:
						root_histogram.FillN(len(x_values), array.array("d", x_values), weights)
					else:
						set_bin_errors = any([bin_error != 0.0 for bin_error in y_errors])
						for x_value, y_value, bin_error in zip(x_values, y_values, y_errors):
							global_bin = root_histogram.FindBin(x_value)
							root_histogram.SetBinContent(global_bin, y_value)
							if set_bin_errors:
								root_histogram.SetBinError(global_bin, bin_error)
				
				elif root_histogram.GetDimension() == 2:
					if len(z_values) == 0:
						root_histogram.FillN(len(x_values), array.array("d", x_values), array.array("d", y_values), weights)
					else:
						set_bin_errors = any([bin_error != 0.0 for bin_error in z_errors])
						for x_value, y_value, z_value, bin_error in zip(x_values, y_values, z_values, z_errors):
							global_bin = root_histogram.FindBin(x_value, y_value)
							root_histogram.SetBinContent(global_bin, z_value)
							if set_bin_errors:
								root_histogram.SetBinError(global_bin, bin_error)
				
				elif root_histogram.GetDimension() == 3:
					root_histogram.FillN(len(x_values), array.array("d", x_values), array.array("d", y_values), array.array("d", z_values), weights)
				
				plotData.plotdict.setdefault("root_objects", {})[nick] = root_histogram
		
		# run upper class function at last
		super(InputInteractive, self).run(plotData)

