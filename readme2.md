# Parallel Monte Carlo Simulation for Estimating Pi

## Description

This project estimates the value of Pi using the Monte Carlo method combined with parallel computing techniques in C. The main idea is to generate a large number of random points inside a square containing an inscribed circle, and then approximate Pi based on the proportion of points that fall inside the circle. By parallelizing this simulation, multiple CPU cores are utilized, allowing for the evaluation of significantly more points in less time, thus achieving a more precise estimation.

## Project Overview

### Fundamental Concept

The Monte Carlo method for calculating Pi is based on the following logic:

- Consider a square of side length 2, centered at the origin, extending from -1 to 1 along both axes.
- A circle with a radius of 1 is inscribed within this square.
- By generating random points within the square, the fraction of points that land inside the circle is proportional to the ratio of the circle’s area to the square’s area.

The area of the circle is:

$$
\text{Area}_{\text{circle}} = \pi \times 1^2 = \pi
$$

and the area of the square is:

$$
\text{Area}_{\text{square}} = 2^2 = 4
$$

Therefore, the relationship between them is:

$$
\frac{\pi}{4} \;=\; \frac{N_{\text{inside}}}{N_{\text{total}}}
$$

where \(N_{\text{inside}}\) is the number of points inside the circle, and \(N_{\text{total}}\) is the total number of generated points. Thus, Pi can be estimated as follows:

$$
\pi \;\approx\; 4 \times \frac{N_{\text{inside}}}{N_{\text{total}}}
$$

### What We Will Do

- **Random Point Generation:**  
  Generate points uniformly in the range \([-1, 1]\) for both \(x\) and \(y\).

- **Point Evaluation:**  
  For each point \((x, y)\), check whether it lies inside the circle using the condition:

  $$
  x^2 + y^2 \;\le\; 1
  $$

- **Parallel Work Distribution:**  
  Divide the total number of points among multiple threads. Each thread counts how many of its assigned points fall inside the circle. Finally, the partial counts are summed.

- **Final Calculation of Pi:**  
  Apply the Monte Carlo formula:

  $$
  \pi \;\approx\; 4 \times \frac{N_{\text{inside}}}{N_{\text{total}}}
  $$

  to obtain the global estimate.

## Why Parallelization Is Beneficial

- **Reduced Execution Time:**  
  Evaluating points concurrently across threads significantly decreases overall computation time.

- **Utilization of Multi-core CPUs:**  
  Modern processors have multiple cores; this approach fully exploits available hardware.

- **Scalability and Precision:**  
  More points can be processed in the same time frame, improving the accuracy of the Pi estimate without sacrificing performance.

## Tools and Technologies

- **Language:** C  
- **Parallelization:** POSIX threads (`pthread`)  
- **Compiler:** GCC or Clang with `-pthread` support
