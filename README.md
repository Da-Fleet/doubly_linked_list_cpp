# Informe Double Linked List en C++

## Integrantes

- Leismael Sosa Hernández
- Alejandro Yero Valdez
- Aldair Alfonso Pérez
- Mauro Bolado Vizoso

## Acerca del proyecto

La idea de este proyecto es implementar una lista doblemente enlazada con C++ usando extensivamente los elementos mas novedosos del lenguaje desde el estándar C++ 11.

Los elementos novedosos que se utilizaron fueron a groso modo los siguientes:

- *punteros inteligentes*
- *funciones lambdas*
- *inferencia de tipos* –> `auto`, `decltype`, `decltype(auto)`
- *nullptr*
- *referencias Rvalue*
- *std::move*
- *foreach*
- *Noexcept*
- *Function*
- *pack expansion*

## Pregunta 2

Los nuevos elementos agregados desde C++ 11 que permiten un manejo ‘inteligente’ de la memoria son los llamados punteros ‘inteligentes’. Estos se dividen en las siguientes categorías de las cuales hablaremos mas adelante:

- `std::unique_ptr`
- `std::shared_ptr`
- `std::weak_ptr`
- `std::auto_ptr` (Obsoleto desde C++ 11)

### unique_ptr

Es una clase template que maneja el tiempo de vida de un objeto guardado dinámicamente. El objeto dinámico es propietario única de un solo puntero `unique_ptr` en todo momento.
La forma de crear un `unique_ptr` es la siguiente:

```Cpp
// Creates a dynamic int with value of 20 owned by a unique pointer
std::unique_ptr<int> ptr = std::make_unique<int>(20);
```

En nuestro proyecto como tal no usamos este puntero en ninguna parte pero valia la pena darle una breve mención. Los punteros que si usamos son los 2 que explicamos a continuación.

### shared_ptr

En algunos programas de C++como la Lista doblemente enlazada de este seminario se hace necesario tener varios punteros apuntando a un mismo objeto (en nuestro caso a un nodo), es decir, hace falta que varios punteros compartan el dominio (`ownership`) del objeto al que apuntan.
A la hora de compartir el *ownership* de un objeto, C++ presenta un puntero especial en la librería estándar llamado `std::shared_ptr`. La implementación de este puntero es mediante una técnica llamada *reference counting*, que guarda la cantidad de punteros `shared_ptr` que apuntan al objeto en cuestión y automáticamente se encarga de bajar el contador cuando se elimina (con delete) alguno de los mismos. Esto permite que cuando se llegue a 0 el objeto sea liberado de memoria automáticamente, quitándole carga al programador.
Un puntero de este tipo se crea de la siguiente forma:

```Cpp
std::make_shared<type>();
```

### weak_ptr

`std::weak_ptr` es para compartir el `ownership` de un objeto temporalmente.
`weak_ptr` puede apuntar a objetos `owned` (poseídos) por punteros `shared_ptr`, convirtiéndose así en dueños temporales del objeto, es decir, no modifican el `reference counter` de un `shared_ptr`.
En nuestra clase `Node` de la Lista doblemente enlazada usamos el puntero `shared_ptr` para apuntar al siguiente nodo y un `weak_ptr` para apuntar al nodo anterior. Esto lo hacemos para ahorrarnos trabajo a la hora de eliminar nodos, puesto que de esta forma al eliminar un nodo `i` el nodo `i+1` tiene una referencia al mismo mediante `prev` pero como es `weak_ptr` no aumenta el reference counter y por ende no impide que se elimine el nodo. Si por el contrario el `prev` fuera también un `shared_ptr` entonces cuando se desea eliminar el nodo `i` con un delete pues el reference counter pasaría de 2 que apuntan al nodo a 1, en vez de a 0 que es lo deseado, es decir, no se eliminaría al momento y tendríamos que hacerle `delete` al `prev` del nodo `i+1`.

### Como usamos los smart pointers

En nuestro código la clase `Node` reducida se vería de la siguiente forma:

```cpp
template <class T>
class Node
{
public:
	T data;
	shared_ptr<Node<T>> next;
	weak_ptr<Node<T>> prev;

	Node(T data);
};
```

### Filosofia de C++ en el manejo de memoria

C++ como tal no tiene una filosofía estándar para el manejo de la memoria. C++ da la libertad y responsabilidad completa al programador de asignar y liberar la memoria dinámica. Aun así, en la comunidad se encuentran patrones a seguir para evitar fuga de memoria. Uno de estos patrones es **RAII** (Resource Acquisition Is Initialization), que plantea en resumen que si un objeto es instanciado en la memoria dinámica dentro de un *scope* pues que debe ser liberado antes de salir del mismo.
Vale la pena destacar que aunque C++ no tiene manejo automático de memoria por defecto, pues que existen librerías que permiten usar un garbage collector y hasta otras que dan la facilidad de usar un *Arena Allocator*

>[!question]+ Que es el Arena Allocator?
>Por arriba se puede decir que el Arena Allocator es una forma de definir la ‘estructura’ en la que se almacenan los datos en la memoria dinamica.
>El Arena Allocator guarda los datos en un espacio de memoria largo y contiguo. Se puede decir que trata de emular algo parecido a un stack

## Pregunta 3

### Que hacen cada uno de los constructores

Un constructor clasico es el que se encarga de inicializar una instancia de un tipo por defecto, inicializando sus miembros.

Los constructores de copia en C++ funcionan con las referencias de l-value y la semántica de copia (la semántica de copia significa copiar los datos reales del objeto a otro objeto en lugar de hacer que otro objeto señale el objeto ya existente en el heap).

Los constructores de movimiento trabajan en las referencias de r-value y semántica de movimiento (la semántica de movimiento implica apuntar al objeto ya
existente en la memoria).

Ejemplo:

```cpp
template <class T>
Node<T>::Node(Node<T> &&other);
```

Al declarar el nuevo objeto y asignarle el r-value, primero se crea un objeto temporal y luego ese objeto temporal se usa para asignar los valores al objeto. Debido a esto, el constructor de copias se llama varias veces y aumenta la sobrecarga y disminuye la potencia computacional del código. Para evitar esta sobrecarga y hacer que el código sea más eficiente, usamos constructores de movimiento.

### Que es Lvalue y Rvalue

En C++ desde sus inicios se permitió el uso de punteros. Esto permite mucha flexibilidad en el lenguaje, pero a veces mas de la deseada. Por ejemplo, si en una función se tiene un parámetro que es un puntero y lo que se quiere es solamente cambiar el valor al que referencia, pero no hacer aritmética de punteros, ni indexar en un array, ni verificar si el puntero es null, pues se tiene mas complejidad que la deseada.

#### Lvalue

Un lvalue es una expresión que produce una referencia de objeto, como un nombre de variable, una referencia de subíndice de matriz, un puntero sin referencia o una llamada de función que devuelve una referencia. Un lvalue siempre tiene una región de almacenamiento definida, por lo que puede tomar su dirección.

Cuales son las diferencias con un puntero?

> - Deben inicializarse en el momento en que se declaran
> - No pueden ser indexados a un offset de la memoria a la que apuntan (como en los punteros)
> - No se puede hacer aritmetica de punteros
> - No se pueden hacer referencias a referencias
> - No se pueden hacer punteros a referencias
> - No se puede hacer un array de referencias
> - No puede ser null
> - No se puede cambiar a lo que le hace ‘alias’

#### Rvalue

Un rvalue es una expresión que no es un lvalue. Los ejemplos de valores r incluyen literales, los resultados de la mayoría de los operadores y llamadas a funciones que devuelven no-referencias. Un rvalue no tiene necesariamente ningún almacenamiento asociado.

Los `Rvalue` crean una referencia que dura solamente para el `scope` donde se creo la referencia. Ejemplo

```Cpp
{
    // 5 es el rvalue
    // No es temporal por esta linea
    // Su tiempo de vida se extiende al scope de r
    int&& r = 5;

    // 434 es el rvalue pero fue asignado a la variable x
    // 434 deja de existir despues del ;
    int x = 434;
 
// Aqui termina el scope d r
// r y 5 terminan su tiempo de vida
// Ninguno puede ser utilizado de aqui en adelante
}
```

Las mismas restricciones que se le aplican a los `Lvalue` se le aplican a los `Rvalue`

## Pregunta 4

La sintaxis del constructor tradicional("()"), por ejemplo, puede parecer unadeclaración de función, y se deben tomar medidas para asegúrese de que la regla deanálisis más molesta del compilador no la confunda con tal. Solo los agregados y los tipos de POD (Plain Old Data) se pueden inicializar con inicializadores agregados("{}").  C++11 proporciona una sintaxis que permite una inicialización de tipo totalmente uniforme que funciona en cualquier objeto usando "{}", esto llama al constructor de la clase. La inicialización uniforme no reemplaza la sintaxis del constructor, que aún se necesita en ocasiones. Si una clase tiene un constructor de lista de inicializadores `TypeName(initializer_list<SomeType>);`, entonces tiene prioridad sobre otras formas de construcción, siempre que la lista de inicializadores se ajuste al tipo del constructor de la secuencia.
En nuestro codigo implementamos esto en la LinkedList de la siguiente forma:

```cpp
template <class T>
LinkedList<T>::LinkedList(initializer_list<T> list)
{
	size = 0;
	for (auto it = list.begin(); it != list.end(); it++)
	{
		this->AddLast(*it);
	}
}
```

## Pregunta 5

En C++11 y versiones posteriores, una expresión lambda, a menudo denominada lambda,
es una manera cómoda de definir un objeto de función anónimo (un cierre)
justo en la ubicación donde se invoca o se pasa como argumento a una función.
Normalmente, las expresiones lambda se usan para encapsular unas líneas de código
que se pasan a algoritmos o métodos asíncronicos.

```cpp

for_each(data.begin(), data.end(), [&](T& item) {
        *this->add(item);
    });

```

En el código anterior se ve claramente la sintaxis del `for_each`, en el cual el tercer argumento es la expresión lambda que es la encargada de por cada elemento contable en data añadirlo dentro del cuerpo de la DoubleLinkedList.

```cpp
LinkedList::~LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}
```

Cuerpo del método de destrucción de la clase LinkedList, en el cual se eliminan los punteros head y tail.
Es necesario luego de crear una nueva instancia de clase, asignar un puntero o la clase almacena los identificadores de los recursos del sistema que deben liberarse, llamar a un método destructor personalizado que se encargue de limpiar lo que escribimos en el constructor. En caso de no declararse el compilador efectivamente crea uno por default, lo cual no dice que cumpla con todo lo que necesitamos limpiar.
Un raw pointer es un puntero con un tiempo de vida no controlado en ningún objeto encapsulado.

## Pregunta 6

El destructor en el caso de la LinkedList si hace falta porque adentro de la misma se crea memoria dinamica para los nodos y estos deben ser eliminados

## Pregunta 7

### Noexecpt

Si una funcion no esta hecha para manejar excepciones se debe usar `noexcept`

### Inferencia de tipos

Dentro de la inferencia de tipos que facilita C++ se encuentran las siguientes:

- `auto`
- `decltype`
- `decltype(auto)`

#### Auto

Auto fue introducido en C++ 11 y en esencia permite la declaracion de variables de forma tal que su tipo sea determinado a partir de los tipos de sus inicializadores.

```cpp
int x = 30; //Aqui se especifica el tipo
auto y = 3.14 // Aqui se infiere que el tipo de 'y' es double
```

La palabra clave `auto` puede ir acompañada de modificadores `&` (referencias) y `const`.

Aun con el poder de ahorrar escritura tiene sus desventajas como la siguiente:

```cpp
int n = 5;
auto y = n, p = 3.14
```

#### Decltype

`decltype` es muy parecido a `auto` en el sentido de que se puede inferir el tipo de una variable. La principal diferencia radica en que `auto` infería a partir del valor que se le asignaba a la variable, mientras que `decltype` necesita que se le ‘pase’ una variable para ‘pegar’ el tipo de esa variable en la nueva variable, es decir, seria algo como lo siguiente:

```cpp
int x = 10;
decltype(x) y; //Aqui y es del mismo tipo que x, de tipo int
```

Que tal si pudiéramos inferirlo, esto es una utilidad que nos brinda decltype y auto y se conoce como late-specified return type (especificación de tipos tardada), ya que el tipo de retorno es asignado en compilación, esto se logra con la siguiente sintaxis:

Una de las grandes ventajas que trae a C++ la incorporación de `decltype` es conocido como `late-specified return type`, que es usado en la sintaxis de funciones y quiere decir que permite que en tiempo de compilación el tipo de retorno de una función sea asignado.

```cpp
template<class T, class U>
auto function(T t, U u) -> decltype (t+u)
{
	return t + u;
}
```

#### Decltype(auto)

El ultimo problema mencionado anteriormente que resuelve `decltype` es mejorado en C++ 14 con la incorporación del keyword `decltype(auto)`. Esto permite que el código anterior pueda ser reescrito de la siguiente forma:

```cpp
template<class T, class U>
decltype(auto) function(T t, U u)
{
	return t + u;
}
```

## Pregunta 8

C++ 11 incorporo al lenguaje un nuevo tipo de template llamado `template parameter pack` que acepta 0 o mas parámetros templates.
Los`template parameter pack` que aceptan 1 o mas parámetros templates se llaman `varidic templates`

Un ejemplo de una clase `varidic template` en acción se puede ver con el siguiente código para crear una tupla

```cpp
template<class... Types>
struct Tuple {};
 
Tuple<> t0;           // Types no contiene argumentos
Tuple<int> t1;        // Types contiene un solo argumento: int
Tuple<int, float> t2; // Types contiene dos argumentos: int y float
Tuple<0> t3;          // error: 0 no es un tipo
```

En el código de arriba aunque se pudo definir una tupla genérica pues no se puede hacer nada con ella.

Un ejemplo de una `varidic function template` que permite definir funciones que reciben cualquier cantidad de parámetros de cualquier tipo es el siguiente:

```cpp
template<class... Types>
void f(Types... args);
 
f();       // OK: args no contiene argumentos
f(1);      // OK: args contiene un solo argumento: int
f(2, 1.0); // OK: args contiene 2 argumentos: int y double
```

### Punteros a funciones

En C++ un puntero a una funcion se define de la siguiente forma:

```cpp
return_type (*function_pointer_name) (T1,..., Tn)
```

donde:

- `return_type` es el tipo de retorno de la función que acepta el puntero
- `function_pointer_name` es el nombre del puntero de función que se esta creando
- `T1, ..., Tn` son los tipos de parámetros que recibe la función a la que el puntero puede apuntar (bien puede estar sin parámetros)

Ejemplo:

```cpp
int sum(int x, int y)
{
	return x + y;
}

int main()
{
	int (*concat)(int,int);
	concat = &sum;
	concat(3,4); // 7
}

```

### Alias

Un `alias` es muy parecido a los `typedef`, en esencia permiten asociar un tipo a un nombre mas simple, pero con la ventaja sobre `typedef` de que puedes usar `templates` sobre el alias.
Un ejemplo de declaración de un `alias` es el siguiente:

```cpp
template<typename T>
using MyAllocList = std::list<T, MyAlloc<T>>;
```

### Puntero a funcion generica con alias

Con los visto en las secciones previas se puede crear un alias a un puntero de una función que permita cualquier cantidad de parámetros de cualquier tipo de la siguiente forma:

```cpp
template <typename R, typename... T>

using Func = R (*)(T...);
```

El código de arriba es el que tenemos implementado en el proyecto de la linked list.
