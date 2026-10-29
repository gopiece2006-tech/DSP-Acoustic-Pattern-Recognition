# DSP-Based Acoustic Pattern Recognition System

## Project Overview
This project implements a DSP-based acoustic pattern analysis and classification system using C programming on the Texas Instruments TMS320C6745 DSP kit.

The program generates three synthetic signals and analyzes their characteristics using digital signal processing techniques.

## Hardware and Software
- **DSP Kit:** Texas Instruments TMS320C6745
- **Programming Language:** C
- **IDE:** Code Composer Studio (CCS)

## Signal Generation
The system generates three types of synthetic signals:

1. **Clap-like signal:** A short, decaying oscillatory waveform.
2. **Whistle-like signal:** A sinusoidal waveform at 2200 Hz.
3. **Background noise:** Low-amplitude pseudo-random noise.

## Signal Configuration
- Sampling frequency: 16,000 Hz
- Number of samples: 1,600
- Signal duration: 0.1 seconds

## DSP Features
The program extracts four signal features:

### 1. RMS Amplitude
Measures the effective magnitude of the signal.

### 2. Peak Amplitude
Measures the maximum absolute sample value.

### 3. Crest Factor
Calculates the ratio of peak amplitude to RMS amplitude.

### 4. Zero-Crossing Rate
Measures how frequently the signal changes sign between consecutive samples.

## Classification
The program applies threshold-based rules to classify each generated signal into one of three categories:

- CLAP-LIKE
- WHISTLE-LIKE
- BACKGROUND-LIKE

## Working Principle
1. Generate a synthetic acoustic signal.
2. Store the samples in an array.
3. Extract RMS amplitude, peak amplitude, crest factor, and zero-crossing rate.
4. Apply threshold-based classification rules.
5. Display the analysis results in the CCS console.
6. Repeat the process for all three signals.

## Limitations
The current implementation uses synthetic signals generated within the program. It does not capture live microphone input.

The classification is based on predefined thresholds and has not been validated against a comprehensive real-world audio dataset.

## Future Enhancements
- Process recorded audio samples.
- Add real-time microphone input.
- Improve the classification algorithm.
- Evaluate classification accuracy using real acoustic data.
- Explore real-time DSP optimization.

## Project Status
Completed: synthetic signal generation, DSP feature extraction, and rule-based classification.

## Learning Outcomes
- Digital signal processing fundamentals
- Embedded C programming
- Acoustic signal feature extraction
- Rule-based classification
- Working with the TMS320C6745 DSP platform

## Author
GOPI GANESH J
THIRD YEAR - ECE