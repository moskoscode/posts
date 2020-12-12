
Já abordamos multithreading aqui no blog, mas em Python. Um dos grandes
empecilhos que vimos lá era a **GIL** (Trava Global do Interpretador) que
impede que mais do que um thread interprete código python a qualquer momento.
Em C++ não temos essa limitação! Mas, para compensar, temos que ser extra
cuidadosos com nossa memória, já que escrever nela ao mesmo tempo que outro
thread a usa pode causar bugs bastante nefários.


