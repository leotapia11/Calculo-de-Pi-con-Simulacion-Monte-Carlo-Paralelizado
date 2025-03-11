# Cálculo de Pi con Simulación Monte Carlo Paralelizado

## Descripción

Este proyecto estima el valor de Pi utilizando el método de Monte Carlo y técnicas de paralelización en C++. La idea central es generar una gran cantidad de puntos aleatorios dentro de un cuadrado que contiene un círculo inscrito y, mediante la proporción de puntos que caen dentro del círculo, aproximar el valor de Pi. Al paralelizar la simulación, se aprovechan múltiples núcleos de la CPU, lo que permite evaluar muchos más puntos en menos tiempo y obtener una estimación más precisa.

## ¿De Qué Trata el Proyecto?

### Concepto Básico

El método de Monte Carlo para calcular Pi se basa en el siguiente razonamiento:

- Se considera un cuadrado de lado 2 centrado en el origen, extendiéndose de -1 a 1 en ambos ejes.
- Dentro de este cuadrado se inscribe un círculo de radio 1.
- Si se generan puntos aleatorios en el cuadrado, la fracción de puntos que caen dentro del círculo es proporcional a la relación entre el área del círculo y el área del cuadrado.

El área del círculo es:

$$
\text{Área}_{\text{círculo}} = \pi \times 1^2 = \pi
$$

y el área del cuadrado es:

$$
\text{Área}_{\text{cuadrado}} = 2 \times 2 = 4
$$

Por lo tanto, la relación entre ambos es:

$$
\frac{\pi}{4} \approx \frac{N_{\text{dentro}}}{N_{\text{total}}}
$$

donde $\( N_{\text{dentro}} \)$ es el número de puntos que caen dentro del círculo y $\( N_{\text{total}} \)$ es el número total de puntos generados. Finalmente, la estimación de Pi se obtiene como:

$$
\pi \approx 4 \times \frac{N_{\text{dentro}}}{N_{\text{total}}}
$$

### ¿Qué Vamos a Hacer?

- **Generación de Puntos Aleatorios:**  
  Se generarán puntos en el rango \([-1, 1]\) para ambos ejes.

- **Evaluación de Puntos:**  
  Cada punto se evaluará para determinar si cae dentro del círculo usando la condición:

  $$
  x^2 + y^2 \leq 1
  $$

- **Distribución del Trabajo en Paralelo:**  
  Se dividirá la tarea entre varios hilos. Cada hilo procesará un subconjunto del total de puntos y contará los puntos que caen dentro del círculo. Luego se combinarán estos resultados.

- **Cálculo Final de Pi:**  
  Se aplicará la fórmula:

  $$
  \pi \approx 4 \times \frac{N_{\text{dentro}}}{N_{\text{total}}}
  $$

  para obtener la estimación global de Pi.

## ¿Por Qué Paralelizarlo es Mejor?

- **Reducción del Tiempo de Ejecución:**  
  La paralelización permite evaluar muchos puntos de forma concurrente, reduciendo significativamente el tiempo total de cómputo.

- **Aprovechamiento de Múltiples Núcleos:**  
  Las CPUs modernas tienen múltiples núcleos, y la solución paralela permite utilizar todos estos recursos para incrementar el rendimiento.

- **Escalabilidad y Precisión:**  
  Procesar un mayor número de puntos en menos tiempo mejora la precisión de la estimación sin comprometer el rendimiento, lo que es ideal para simulaciones que requieren evaluar millones de puntos.

## Herramientas y Tecnologías

- **Lenguaje:** C++
- **Librerías Estándar:**
  - `<iostream>` para entrada/salida.
  - `<thread>` y `<mutex>` para la paralelización y sincronización.
  - `<random>` para la generación de números aleatorios.
  - `<atomic>` para la gestión segura de contadores compartidos.
  - `<chrono>` para medir tiempos de ejecución.
- **Compilador:** C++11 o superior (por ejemplo, g++ o clang++).
