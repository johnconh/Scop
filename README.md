# SCOP

Scop es un proyecto desarrollado para explorar y profundizar en las capacidades de OpenGL, la API estándar para gráficos en 3D. El objetivo principal de este proyecto es proporcionar una herramienta para cargar, visualizar y manipular modelos 3D en formato .obj, aplicando técnicas básicas de renderizado y texturizado. Scop busca ofrecer una base sólida para entender los conceptos fundamentales de gráficos por computadora y la programación con OpenGL.

## Características Principales
    1.-Carga de Modelos 3D:
        .Capacidad para cargar archivos en formato .obj.
        .Lectura y procesamiento de vértices, caras y normales desde archivos .obj.

    2.-Renderizado y Shading:
        .Implementación de un pipeline de renderizado básico.
        .Uso de shaders programables en GLSL para la vertex y fragment shader.
        .Cálculo de iluminación básica utilizando el modelo de iluminación de Phong.

    3.-Texturizado:
        .Soporte para cargar texturas desde archivos de imagen.
        .Mapeo UV para aplicar texturas a modelos 3D.
        .Capacidad para alternar entre el color de material y el texturizado mediante una combinación de teclas.

    4.-Interacción en Tiempo Real:
        .Manipulación de la cámara para permitir la visualización interactiva del modelo.
        .Rotación automática del modelo y movimiento basado en la entrada del usuario.
        .Sistema de entrada para alternar entre modos de renderizado y otras funcionalidades.

## Object Files(.obj)
[.obj file](https://en.wikipedia.org/wiki/Wavefront_.obj_file) El formato de archivo OBJ es un formato de datos simple que representa solo la geometría 3D, es decir, la posición de cada vértice, las caras que forman cada polígono definido como una lista de vértices.

## Material (.mtl)
[Material](https://paulbourke.net/dataformats/mtl/) es utilizado junto con los archivos '.obj' para definir las porpiedades de los materiales que se aplicaran en los modelos 3D. Estos archivos contienen información sobre cómo deben renderizarse los objetos, especificando colores, texturas y otros parámetros visuales.
- Cada línea define una propiedad del material:
    - newmtl: Define el comienzo de un nuevo material con un nombre especificado.
    - Ka: Color ambiental del material, representado como un vector RGB.
    - Kd: Color difuso del material, representado como un vector RGB.
    - Ks: Color especular del material, representado como un vector RGB.
    - Ns: Exponente especular que determina el tamaño y la intensidad del brillo especular.
    - Ni: Índice de refracción que afecta cómo se refracta la luz al pasar a través del material.
    - d: Factor de transparencia del material (1.0 es completamente opaco y 0.0 es completamente transparente).
    - illum: Modelo de iluminación utilizado para el material:
        - 0: Color de sombreado.
        - 1: Sombreado sin reflejos.
        - 2: Sombreado con reflejos.

## KEYS
Utilizo funciones GLFW básicas para manejar las entradas.

```
    Mover el Objeto:
        Tecla W: hacia arriba
        Tecla S: hacia abajo
        Tecla A: Izquierda
        Tecla D: Derecha
        Tecla Q: Acercarse
        Tecla E: Alejarse
    
    Mover la camara:
        Tecla 8: hacia arriba
        Tecla 3: hacia abajo
        Tecla 4: Izquierda
        Tecla 6: Derecha
        Tecla +: Acercarse
        Tecla -: Alejarse
    
    Cambio de textura a color Tecla T.
    Cambio de color gris a color RGB: Tecla C.
    Cambio al modo WireFrame: Tecla Y.

```

## Como Ejecutar

- Make
- ./scop path/to/your/model.obj
