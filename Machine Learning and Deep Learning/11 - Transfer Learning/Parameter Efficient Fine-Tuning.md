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

