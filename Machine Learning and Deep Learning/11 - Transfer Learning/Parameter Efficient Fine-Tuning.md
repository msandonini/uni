---
tags:
  - deep_learning
  - transfer_learning
---
Full fine-tuning entails updating all model parameters, but this leads to:
- High computational demand (often requires thousands of GPUs in parallel)
- High memory footprint
- Redundancy when adapting to multiple downstream tasks
- Loss of generalization (overwriting pre-trained knowledge, leading to reduced performance on tasks outside the fine-tuning domain)

Basically, fine tuning large models is increasingly impractical due to their vast number of parameters and high computational costs. This becomes more and more inefficient and unsustainable as model sizes keep growing.

