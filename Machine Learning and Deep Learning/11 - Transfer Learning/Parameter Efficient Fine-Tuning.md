---
tags:
  - deep_learning
  - transfer_learning
  - transformers
---
Full fine-tuning entails updating all model parameters, but this leads to:
- High computational demand (often requires thousands of GPUs in parallel)
- High memory footprint
- Redundancy when adapting to multiple downstream tasks
- Loss of generalization (overwriting pre-trained knowledge, leading to reduced performance on tasks outside the fine-tuning domain)

Basically, fine tuning large models is increasingly impractical due to their vast number of parameters and high computational costs. This becomes more and more inefficient and unsustainable as model sizes keep growing.

In order to make fine-tuning more efficient several approaches are used, depending on how and where the model is used:
- Prompt tuning

## Prompt Tuning

In the context of a [[Transformers|transformer]], a [[token]] represents a unit of input (e.g. a word/subword), and a [[prompt]] is a sequence of such tokens that conditions the model's behavior during inference or training.

Prompt tuning is one of the most lightweight [[Parameter Efficient Fine-Tuning|Parameter-Efficient Fine Tuning (PEFT)]] techniques

[[Visual Prompt Tuning (VPT)]] is a variant of prompt tuning which uses visual prompts to fine tune vision models. It has 2 variants:
- Shallow
- Deep


