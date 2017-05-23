Juego de la vida
================

Esta implemntación del conocido [juego de la vida](https://es.wikipedia.org/wiki/Juego_de_la_vida) ideado por [John Horton Conway](https://es.wikipedia.org/wiki/John_Horton_Conway) en 1970. forma parte del Curso de Programación en C Moderno impartido por el Centro de Formación Permanente de la Universidad de Sevilla que he cursado este año 2017.

Reglas del juego
----------
Se dice que es un juego de 0 jugadores porque el usuario no puede (a priori) interactuar con el juego. Dada una configuración inicial, el juego sigue una trayectoria totalmente determinista. El juego consiste en un array bidimensional de "celulas" que pueden estar "vivas" o "muertas". El juego evoluciona siguiendo dos reglas muy simples:

* Una célula muerta, sólo nacerá en la siguiente iteración, si tiene exactamente 3 vecinas vivas
* Una célula viva, sólo sobrevivirá en la siguiente iteración, si tiene 2 ó 3 vecinas vivas.

Nota: consideramos que cada célula tiene 8 vecinas, que son las que tocan en una arista o vértice a la célula central.
