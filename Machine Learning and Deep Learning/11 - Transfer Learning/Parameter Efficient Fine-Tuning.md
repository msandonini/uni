---
tags:
  - deep_learning
  - transfer_learning
  - transformers
  - fine_tuning
aliases:
  - PEFT
  - Parameter-Efficient Fine-Tuning (PEFT)
---
Full [[Fine Tuning|fine tuning]] entails updating all model parameters, but this leads to:
- High computational demand (often requires thousands of GPUs in parallel)
- High memory footprint
- Redundancy when adapting to multiple downstream tasks
- Loss of generalization (overwriting pre-trained knowledge, leading to reduced performance on tasks outside the fine-tuning domain)

Basically, fine tuning large models is increasingly impractical due to their vast number of parameters and high computational costs. This becomes more and more inefficient and unsustainable as model sizes keep growing.

In order to make fine-tuning more efficient several approaches are used, depending on how and where the model is used:
- [[#Prompt Tuning]]
- [[#Prefix Tuning]]
- [[#Adaptation-based Fine Tuning]]
- [[#Reparameterization-based fine tuning]]

## Prompt Tuning

In the context of a [[Transformers|transformer]], a [[token]] represents a unit of input (e.g. a word/subword), and a [[prompt]] is a sequence of such tokens that conditions the model's behavior during inference or training.

Prompt tuning is one of the most lightweight [[Parameter Efficient Fine-Tuning|Parameter-Efficient Fine-Tuning (PEFT)]] techniques

### Visual Prompt Tuning (VPT)

[[Visual Prompt Tuning (VPT)]] is a variant of prompt tuning which uses visual prompts to fine tune vision models. It has 2 variants:
- Shallow
- Deep

By using tokens prepended to the prompt, in [[Visual Prompt Tuning (VPT)|VPT]] we can influence the weights of other parameters in the model.

## Prefix Tuning

Prefix tuning is a [[Parameter Efficient Fine-Tuning|PEFT]] method based on prefix vectors, which influence attention distributions.
This technique introduces trainable key/value vectors $P^{K}$ and $P^{V}$ of length $l$ prepended to each attention layer. For each layer:
$$
\begin{align}
&K' = [P^{K} || K] \\
&V' = [P^{V} || V]
\end{align}
$$
These vectors may be either static or generated dynamically by a small prefix [[encoder]] (often an [[MLP]]), shared across layers or layer-specific

- Parameter-efficient
	- less than 1% of model parameters are trained
- No full model duplication
	- Suitable for multi-task and low-resource settings
- Preserve pre-trained knowledge
	- Core transformer weights remain frozen

Usually, prefix tuning outperforms prompt tuning.

## Adaptation-based Fine Tuning

### AdaptFormer

[[AdaptFormer]] is an adapter-based fine-tuning method that uses a small number of adapter to fine-tune large models.
The adapters are small [[MLPs]] added to the model's intermediate layers (after the [[LayerNorm]]), and are used to adapt the model to a new task.

In AdaptFormers the $s$ parameter is a stability value which acts as multiplier defining how much to overwrite the original knowledge and, as a consequence, if the model is able to adapt fast or slowly to the new data.

## Reparameterization-based fine tuning

Reparameterization-based fine tuning is a [[Parameter Efficient Fine-Tuning|PEFT]] strategy where model updates are expressed via structured, low-dimensional transformations rather than directly updating full weight matrices.
$$
W' = W_{0} + \Delta W, \text{ where } \Delta W = f_{\theta}(\cdot)
$$
In this general form, $W_{0}$ is the pre-trained weight matrix and $f_{\theta}$ is a structured function (e.g. low-rank, sparse, or generated).
