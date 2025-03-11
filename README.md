# Calculo de Pi con Simulacion Monte-Carlo Paralelizado
## Descripción

Este proyecto estima el valor de Pi utilizando el método de Monte Carlo y técnicas de paralelización en C++. La idea central es generar una gran cantidad de puntos aleatorios dentro de un cuadrado que contiene un círculo inscrito. Al calcular la proporción de puntos que caen dentro del círculo, se puede aproximar el valor de Pi. La paralelización mejora el rendimiento, permitiendo procesar un mayor número de puntos en menos tiempo y aprovechando múltiples núcleos de la CPU.

## ¿Qué vamos a hacer?

### Concepto Básico

El método de Monte Carlo para calcular Pi se basa en el siguiente razonamiento:

- Se considera un cuadrado de lado 2 centrado en el origen, por ejemplo, extendiéndose de -1 a 1 en ambos ejes.
- Dentro de este cuadrado se puede inscribir un círculo de radio 1.
- Si se generan puntos aleatorios en el cuadrado, la fracción de puntos que caen dentro del círculo es proporcional a la relación entre el área del círculo y el área del cuadrado.
- El área del círculo es $\(\pi \times r^2\) (con \(r = 1\), simplemente \(\pi\)) y el área del cuadrado es \(4\)$.
- Por lo tanto, la relación es:
  \[
  \frac{\pi}{4} \approx \frac{N_{\text{dentro}}}{N_{\text{total}}}
  \]
  donde \(N_{\text{dentro}}\) es el número de puntos que caen dentro del círculo y \(N_{\text{total}}\) es el número total de puntos generados.
- De esta forma, la estimación de Pi se obtiene como:
  \[
  \pi \approx 4 \times \frac{N_{\text{dentro}}}{N_{\text{total}}}
  \]

- **Generación de Puntos Aleatorios:** Cada hilo se encargará de generar y evaluar una parte del total de puntos.
- **Evaluación de Puntos:** Determinar si cada punto se encuentra dentro del círculo inscrito en el cuadrado.
- **Estimación de Pi:** Combinar los resultados de todos los hilos para calcular una estimación global del valor de Pi.
- **Paralelización:** Utilizar `std::thread` para distribuir el trabajo de forma concurrente, optimizando el tiempo de ejecución y permitiendo escalar el número de puntos evaluados.

## Herramientas y Tecnologías

- **Lenguaje:** C++
- **Librerías Estándar:**  
  - `<iostream>` para entrada/salida.
  - `<thread>` y `<mutex>` para la paralelización y sincronización.
  - `<random>` para la generación de números aleatorios.
  - `<chrono>` para medir tiempos de ejecución.
- **Compilador:** C++11 o superior (por ejemplo, g++ o clang++).

## ¿Por qué paralelizarlo es mejor?

- **Reducción del Tiempo de Ejecución:** Al dividir la carga de trabajo entre varios hilos, se pueden generar y evaluar más puntos en menos tiempo, lo que mejora la precisión de la estimación.
- **Aprovechamiento de Múltiples Núcleos:** Las CPUs modernas tienen varios núcleos; la paralelización permite utilizar toda la capacidad de procesamiento disponible.
- **Escalabilidad:** La solución se puede escalar fácilmente aumentando el número de hilos, lo que resulta especialmente útil para simulaciones que requieren millones de puntos.

## Pasos a Seguir

1. **Definir el Problema y la Fórmula de Estimación:**
   - Utilizar la relación:
     \[
     \pi \approx 4 \times \frac{\text{número de puntos dentro del círculo}}{\text{número total de puntos}}
     \]
2. **Implementar la Versión Secuencial:**
   - Desarrollar un prototipo que genere puntos aleatorios y calcule la proporción de puntos dentro del círculo.
3. **Diseñar la Estrategia de Paralelización:**
   - Decidir el número de hilos a usar y dividir la cantidad total de puntos entre ellos.
   - Cada hilo deberá tener su propio generador de números aleatorios para asegurar la independencia de los datos.
4. **Implementar la Versión Paralela:**
   - Utilizar `std::thread` para lanzar múltiples tareas que realicen la simulación de forma concurrente.
   - Sincronizar la recolección de resultados utilizando mecanismos como `std::mutex` para evitar condiciones de carrera.
5. **Combinar Resultados y Calcular Pi:**
   - Al finalizar, sumar los resultados de cada hilo y aplicar la fórmula de estimación de Pi.
6. **Validación y Pruebas de Rendimiento:**
   - Comparar la estimación con el valor real de Pi.
   - Medir el tiempo de ejecución y ajustar la cantidad de puntos y hilos para optimizar el rendimiento.
