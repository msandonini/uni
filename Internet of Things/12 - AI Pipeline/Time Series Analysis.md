---
tags:
  - iot
  - time_series
  - deep_learning
  - machine_learning
---
[[Time Series]] are used in IoT since in real world scenarios we find continuous sensor data streams, with high volume, velocity and variety.

In an IoT context Time Series are usually used for these scopes:
- Predictive maintenance
	- Detect equipment degradation
	- Plan maintenance early
- Sensor fault detection
	- Identify drift or failure
	- Real-time alerts

A Time Series is basically a series of points sampled in time at regular intervals.
$$
y_{t} = [y_{1}, y_{2}, \dots, y_{N}]
$$
- univariate
	- $n = 1$
- multivariate
	- $n > 1$

Time series are useful since they enable to study trends and seasonality of the analysed data, and they can be used to analyse frequency of data.

With time series we can do basically 4 tasks:
- Classification
- Imputation
- [[#Time series forecasting|Forecasting]]
- [[#TS Anomaly Detection|Anomaly detection]]

Here we will focus in forecasting and anomaly detection.

## Time series forecasting

The idea is very simple: we want to forecast 

There are various methods to do so:
- [[#Naive methods|Naives]]
- [[#Statistical methods|Stats-based]]
- [[#Machine Learning methods|Machine Learning]]
- [[#Deep Learning methods|Deep Learning]]
Each method is a trade-off: simpler (naive and stats-based) methods require less data and less computation power, but they are less performant, while ML and DL require more computation and data, but lead to the best performance.

### Naive methods
The 2 simplest methods are:
- Mean / Last value
- Naive shift
These 2 are the simplest, but not very useful methods, while other, more useful, methods are:
- Moving average
- Exponential smoothing
	- Also called Exponential Smoothing Average
	- It's basically the weighted average of past observations with exponentially decreasing weights
$$
\hat{y}_{t+1} = \alpha y_{t} + (1-\alpha) \hat{y}_{t}
$$

### Statistical methods

- ARMA
- [[#ARIMA]]
- SARIMA
- VARIMA
All models have similar names since they are combinations of different submodels, where AR stands for *autoregressive* and MA for *moving average*.

#### ARIMA

$$
(1 - \phi_{1} B - \dots - \phi_{b} B^{p}) (1-B)^{d} y_{t} = c + (1 + \theta_{1} B + \dots + \theta_{q} B^{q}) \varepsilon_{t}
$$
- $p$ = order of the autoregressive part (to use the past steps)
	- $(1 - \phi_{1} B - \dots - \phi_{b} B^{p})$
- $d$ = degree of first differencing involved (to remove trends)
	- $(1-B)^{d} y_{t}$
- $q$ = order of the moving average part (models error)
	- $c + (1 + \theta_{1} B + \dots + \theta_{q} B^{q}) \varepsilon_{t}$
- $B$ = lag operator

#### FB-Prophet

Designed from Facebook (now Meta), it's designed to handle seasonality.

### Machine Learning methods

ML based methods are useful with multivariate Time Series, which can be represented as Regression tasks.

Some examples of ML methods usable are:
- [[Random Forest]]
- [[SVR]]

### Deep Learning methods

These are often tailored on specific datasets.
They generally require more data and compute power.

Some examples of DL methods usable are:
- [[RNN]] / [[LSTM]]
- [[Transformers]]

## Time series Anomaly Detection

*Anomaly* is a statistical term that may not correspond to one's self meaning of the same term

- Threshold-based
	- Defines a threshold over which the value will be considered an anomaly
- Z-score / Deviation
	- Like the threshold method, but a bit more advanced to watch deviation
$$
Z = \frac{x - \mu}{\sigma}
$$
- Rolling window check

To apply anomaly detection, we must train it on a "normal" dataset (with no anomalies), since anomalies, by definition, are rare.


### ML/DL methods

Examples of ML/DL algorithms usable in time series analysis are:
- Isolation forest / One-class SVM
- [[Autoencoders]]
