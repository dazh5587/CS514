# Loss Classifier

This directory contains code and data for classifying loss-based CCA flows. The classifier uses time-series clustering via K-Means to classify the loss traces using Dynamic Time Warping (DTW) and resampling.

Implementation for this can be found in `loss_classifier.ipynb`.

## Data

The data in this directory is generated from a custom NS3 simulation of various CCAs. The data is stored in the `data/` directory. The data is stored in CSV format but placed inside text files. The data is organized as follows:

Each of the 500 rows represents a flow. The 600 comma separated values are samples of the CWND taken every 0.1 seconds for a total of 60 seconds. This format is used in each text file and the names are representative of the CCA used in the simulation.

## Requirements

The following packages are required to run the code in this directory. Please use the `requirements.txt` file to install these packages.

- numpy
- matplotlib
- tslearn

We reccomend using a Python virtual environment to install these packages as tslearn is not currently supported beyond Python 3.10.