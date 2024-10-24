# Вычисление числа π методом монте карло

## Описание задачи 

Требуется определить число π по методу Монте-Карло.
Именно, пусть в квадрат со стороной 2r бросается дротик (монетка, кошка или другой предмет). Нарисуем внутри квадрата вписанную
окружность с радиусом r. Ясно, что отношение количества попаданий в
окружность к общему количеству бросков будет равно π/4. 
Следовательно, число π можно представить как
$ π ≈ {4 * Количество попаданий в окружность \over
Общее количество бросков} $

## Формат входных данных 

Формат входных данных. Запуск программы из командной строки
***./program nthreads ntrials***,
где ***nthreads*** — количество потоков,
***ntrials*** — общее количество попыток.

## Формат выходных данных

Вывести на экран получившееся число π

# Отчет

Файл **monte_carlo_single_thread.c** был создан специально для отдельного замера времени работы последовательной программы, чтобы исключить засчитывание времени на создание единственного отдельного потока (хоть оно, вероятно, и пренебрежимо мало).

Ниже представлены замеры времени при различных параметрах 

## Время

| nthreads \ ntrials | 131072   |  262144  |  542288  | 1048576  | 2097152   | 3276800  | 6553600   | 13107200 | 26214400 |
| ------             | ------   | ------   | ------   | ------   | ------    | ------   | ------    | ------   | ------   | 
| 1                  | 0.008972 | 0.015530 | 0.031539 | 0.059824 | 0.113632  | 0.174821 | 0.346076  | 0.681595 | 1.394928 |
| 2                  | 0.006254 | 0.010809 | 0.018016 | 0.031380 | 0.066904  | 0.099653 | 0.189712  | 0.354813 | 0.726676 |
| 3                  | 0.003560 | 0.005900 | 0.014326 | 0.024102 | 0.046859  | 0.075726 | 0.150995  | 0.248597 | 0.487973 |
| 4                  | 0.003933 | 0.006310 | 0.011473 | 0.019616 | 0.048463  | 0.056522 | 0.113325  | 0.201161 | 0.395917 |
| 5                  | 0.003230 | 0.005186 | 0.009028 | 0.016531 | 0.030906  | 0.050280 | 0.090786  | 0.200436 | 0.350928 |
| 6                  | 0.002921 | 0.005111 | 0.008020 | 0.015257 | 0.027465  | 0.042382 | 0.081040  | 0.157059 | 0.309586 |
| 7                  | 0.002543 | 0.004380 | 0.009062 | 0.015160 | 0.024998  | 0.039377 | 0.074900  | 0.166144 | 0.277591 |
| 8                  | 0.003156 | 0.006244 | 0.009359 | 0.016528 | 0.021580  | 0.037577 | 0.069267  | 0.161369 | 0.266720 |

## Ускорения 

| nthreads \ ntrials | 131072   |  262144  |  542288  | 1048576  | 2097152   | 3276800  | 6553600   | 13107200 | 26214400 |
| ------             | ------   | ------   | ------   | ------   | ------    | ------   | ------    | ------   | ------   | 
| 2                  | 1.434645 | 1.4367   | 1.750610 | 1.906437 | 1.698434  | 1.754297 | 1.824218  | 1.920998 | 1.919601 |
| 3                  | 2.520254 | 2.63220  | 2.20152  | 2.482117 | 2.424977  | 2.308599 | 2.291970  | 2.741767 | 2.858617 |
| 4                  | 2.281543 | 2.461172 | 2.74897  | 3.049755 | 2.344717  | 3.092973 | 3.053836  | 3.388306 | 3.523284 |
| 5                  | 2.777754 | 2.99460  | 3.49346  | 3.618898 | 3.676697  | 3.476949 | 3.811997  | 3.400562 | 3.974969 |
| 6                  | 3.071554 | 3.03854  | 3.93254  | 3.921085 | 4.137338  | 4.124888 | 4.270434  | 4.339739 | 4.505785 |
| 7                  | 3.528116 | 3.54544  | 3.48035  | 3.946174 | 4.545644  | 4.439673 | 4.620507  | 4.102435 | 5.025120 |
| 8                  | 2.842839 | 2.48718  | 3.369911 | 3.619555 | 5.265616  | 4.652341 | 4.996261  | 4.223829 | 5.229934 |

## Эффективность

| nthreads \ ntrials | 131072   |  262144  |  542288  | 1048576  | 2097152   | 3276800  | 6553600   | 13107200 | 26214400 |
| ------             | ------   | ------   | ------   | ------   | ------    | ------   | ------    | ------   | ------   | 
| 2                  | 0.717322 | 0.718350 | 0.875305 | 0.953218 | 0.849217  | 0.877148 | 0.912109  | 0.960499 | 0.959800 |
| 3                  | 0.840085 | 0.877400 | 0.733840 | 0.827372 | 0.808326  | 0.769533 | 0.763990  | 0.913922 | 0.913923 |
| 4                  | 0.570385 | 0.615293 | 0.687242 | 0.762439 | 0.586179  | 0.773243 | 0.763459  | 0.847077 | 0.880821 |
| 5                  | 0.555551 | 0.598920 | 0.698692 | 0.723780 | 0.735339  | 0.695390 | 0.762399  | 0.680112 | 0.794994 |
| 6                  | 0.511926 | 0.506423 | 0.655423 | 0.653514 | 0.689556  | 0.687481 | 0.711739  | 0.723290 | 0.750964 |
| 7                  | 0.504017 | 0.506491 | 0.497193 | 0.563739 | 0.649378  | 0.634239 | 0.660072  | 0.586062 | 0.717874 |
| 8                  | 0.355355 | 0.310897 | 0.421239 | 0.452444 | 0.658202  | 0.581543 | 0.624533  | 0.527979 | 0.653742 |
 
## Вывод

Из интересных моментов можно отметить, что эффективность работы алгоритма сильно проседает при маленьком количестве точек и большом количестве потоков. Можно предположить, что такое происходит из-за того, что сама по себе операция создания потока довольно тяжелая, в связи с чем на маленьком кол-ве данных проще запустить алгоритм на одном потоке, вместо того чтобы тратить время на создание других потоков и распаралелливать мелкую задачу.