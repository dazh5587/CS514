# CS 514 Final Project: Time-Series Clustering for CCA Identification

This repo is for the final project of Duke ECE 558/CS 514. Our goal is to build a system to classify CCAs and improve on previous works such as [Nebby](https://www.comp.nus.edu.sg/~bleong/publications/sigcomm24-nebby.pdf)

The original paper uses polynomial fitting on segmented BiF traces as a way to classify CCAs. We will use time-series clustering to classify CCAs.

# Repository Structure

This repository contains multiple parts, each of which is in a separate directory. The following is a brief description of each part:

- `loss_classifier/`: Contains the data and Jupyter notebook for the loss-based classifier. This implementation uses Time Series Clustering via K-Means to classify the loss traces using DTW and resampling.
- `no_loss_classifier/`: Contains the data and Jupyter notebook for the non loss-based classifier.
- `nebby_classifier/`: Contains the subfolder from the Nebby repository that is used to reproduce Nebby's results given a BiF file.
- `sample_ns3_code/`: Contains an example of an ns-3 simulation to capture the CWND trace of a congestion control algorithm. The code was adapted from this [tutorial](https://spoken-tutorial.org/watch/ns-3+Network+Simulator/Analyzing+TCP+Congestion+window/English/).

The root folder also contains our final report and presentation slides.