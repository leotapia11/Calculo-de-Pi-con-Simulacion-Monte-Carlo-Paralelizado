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
\text{Area}_{\text{square}} = 2 \times 2 = 4
$$

Therefore, the relationship between them is:

$$
\frac{\pi}{4} \approx \frac{N_{\text{inside}}}{N_{\text{total}}}
$$

where \( N_{\text{inside}} \) is the number of points inside the circle, and \( N_{\text{total}} \) is the total number of generated points. Thus, Pi can be estimated as follows:

$$
\pi \approx 4 \times \frac{N_{\text{inside}}}{N_{\text{total}}}
$$

### What We Will Do

- **Random Point Generation:**  
  Points will be generated within the range \([-1, 1]\) for both axes.

- **Point Evaluation:**  
  Each generated point will be evaluated to determine if it lies inside the circle using the condition:

  $$
  x^2 + y^2 \leq 1
  $$

- **Parallel Work Distribution:**  
  The task will be divided among multiple threads. Each thread processes a subset of the total points, counting those that fall inside the circle. Afterwards, these results are combined.

- **Final Calculation of Pi:**  
  Using the formula:

  $$
  \pi \approx 4 \times \frac{N_{\text{inside}}}{N_{\text{total}}}
  $$

  we obtain the global Pi estimation.

## Why Parallelization Is Beneficial

- **Reduced Execution Time:**  
  Parallelization allows many points to be evaluated concurrently, significantly decreasing overall computation time.

- **Utilization of Multi-core CPUs:**  
  Modern CPUs contain multiple cores. The parallel solution exploits these resources, greatly enhancing performance.

- **Scalability and Precision:**  
  Evaluating more points in less time improves estimation accuracy without sacrificing performance, ideal for simulations requiring millions of points.

## Tools and Technologies

- **Language:** C
