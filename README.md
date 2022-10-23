# Informe Double Linked List en C++

## Integrantes

- Leismael Sosa Hernández
- Alejandro Yero Valdés
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

## Pregunta 1

Se implementaron las clases `template`: `LinkedList` y `Node` para la lista doblemente enlazada genérica. `Node` esta conformado por un puntero al siguiente nodo, un puntero al nodo anterior y un puntero al dato que contiene. `LinkedList` esta conformado por un puntero al primer nodo, un puntero al último nodo y un entero que representa el tamaño de la lista. Cada clase tiene sus respectivos constructores, destructores, getters y métodos para agregar y eliminar nodos.

## Pregunta 2

Los nuevos elementos agregados desde C++ 11 que permiten un manejo "inteligente" de la memoria son los llamados punteros ‘inteligentes’. Estos se dividen en las siguientes categorías de las cuales hablaremos mas adelante:

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

#### shared_ptr

La implementación de este puntero es mediante una técnica llamada `reference counting`, que guarda la cantidad de punteros `shared_ptr` que apuntan al objeto en cuestión y automáticamente se encarga de bajar el contador cuando se elimina (con delete) alguno de los mismos. Esto permite que cuando se llegue a 0 el objeto sea liberado de memoria automáticamente, quitándole carga al programador.
Un puntero de este tipo se crea de la siguiente forma:

```Cpp
std::make_shared<T>(T object);
```

Esto resulta muy util cuando se tiene un objeto que es compartido por varios objetos, como por ejemplo un objeto `Node`. En este caso, cada `Node` tiene un puntero al dato que contiene y un puntero al siguiente nodo. Si se tiene una lista de `Node` y se elimina un `Node` de la lista, el `Node` eliminado todavía tiene un puntero al dato que contiene y al siguiente nodo, por lo que si se elimina el `Node` y no se elimina el dato que contiene, se genera un memory leak. Para evitar esto, se puede crear un puntero `shared_ptr` al dato que contiene y así se asegura que el dato no se elimine hasta que no se eliminen todos los `Node` que lo contienen. De esta forma, se puede eliminar un `Node` de la lista sin tener que preocuparse de eliminar el dato que contiene.

### weak_ptr

Funciona igual que un `shared_ptr`, puede apuntar a objetos `owned` (poseídos) por punteros `shared_ptr`, pero convirtiéndose así en dueños temporales del objeto, es decir, no modifican el `reference counter` de un `shared_ptr`.

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

Como se puede ver, el puntero al dato que contiene es de tipo `shared_ptr` y el puntero al nodo anterior es de tipo `weak_ptr`. Si se utilizaría un `shared_ptr` para el nodo anterior, ocurre una dependencia cíclica:

```cpp
object A --> object B -- > object C 
	^           / ^           /
	 \---------/   \---------/
```

 Lo que implica que si se elimina `object B`, el `reference counting` baja a 1, por lo que no se destruye de la memoria y esto es lo que se necesita. Si se utiliza un `weak_ptr` para el nodo anterior, se evita esta dependencia cíclica y se puede eliminar `object B` sin problemas.

### Filosofía de C++ en el manejo de memoria

C++ como tal no tiene una filosofía estándar para el manejo de la memoria. C++ da la libertad y responsabilidad completa al programador de asignar y liberar la memoria dinámica. Aun así, en la comunidad se encuentran patrones a seguir para evitar fuga de memoria. Uno de estos patrones es **RAII** (Resource Acquisition Is Initialization), que plantea en resumen que si un objeto es instanciado en la memoria dinámica dentro de un *scope* pues que debe ser liberado antes de salir del mismo.
Vale la pena destacar que aunque C++ no tiene manejo automático de memoria por defecto, pues que existen librerías que permiten usar un garbage collector. Una de estas librerías es `boost::smart_ptr` que permite usar punteros inteligentes como `unique_ptr` y `shared_ptr`.

### Alias para simplificar nombres de tipos

En C++ se pueden crear alias para simplificar el nombre de tipos. Esto se hace mediante la palabra reservada `using`. Por ejemplo, si se tiene un tipo `std::shared_ptr<std::vector<std::string>>` y se quiere simplificar el nombre, se puede hacer de la siguiente forma:

```cpp
using string_vector = std::vector<std::string>;
using string_vector_ptr = std::shared_ptr<string_vector>;
```

Para la implementación de la clase `Node` se puede usar un alias para simplificar el nombre del tipo `shared_ptr<Node<T>>`:

```cpp
template <class T>
class Node
{
public:
	T data;
	using node_ptr = std::shared_ptr<Node<T>>;
	node_ptr next;
	using node_weak_ptr = std::weak_ptr<Node<T>>;
	node_weak_ptr prev;
};
```

Para la implementación de la clase `LinkedList` se puede usar un alias para simplificar el nombre del tipo `shared_ptr<Node<T>>`:

```cpp
template <class T>
class LinkedList
{
public:
	using node_ptr = std::shared_ptr<Node<T>>;
	using node_weak_ptr = std::weak_ptr<Node<T>>;
	node_ptr head;
	node_ptr tail;
	int size;
};
```

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

Si una clase tiene un constructor de lista de inicializadores `TypeName(initializer_list<SomeType>);`, entonces tiene prioridad sobre otras formas de construcción, siempre que la lista de inicializadores se ajuste al tipo del constructor de la secuencia:

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

De esta forma, se puede crear una lista enlazada a partir de una lista de inicialización:

```cpp
LinkedList<int> list = {1, 2, 3, 4, 5};
```

Que es equivalente a hacerlo en `C#`.

### Comparación con de `()` y `{}`

Los paréntesis se usan para invocar funciones, mientras que las llaves se usan para inicializar objetos. Por ejemplo, `std::vector` tiene un constructor que toma un tamaño y un valor por defecto:

```cpp
std::vector<int> v(10, 0);
```

Esto crea un vector de 10 elementos, todos con valor 0. Sin embargo, si se usa una lista de inicialización, se puede crear un vector con los valores especificados:

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
```

## Pregunta 5

En C++11 y versiones posteriores, una expresión lambda, a menudo denominada lambda, es una manera cómoda de definir un objeto de función anónimo justo en la ubicación donde se invoca o se pasa como argumento a una función.
Normalmente, las expresiones lambda se usan para encapsular unas líneas de código
que se pasan a algoritmos o métodos asíncronicos. Además, se implementa un constructor que recibe un `vector<T>`:

```cpp
LinkedList(vector<T> data){
	size = 0;
    for_each(data.begin(), data.end(), [&](T &item)
             { this->AddLast(item); });
}
```

En el código anterior se ve claramente la sintaxis del `for_each`, en el cual el tercer argumento es la expresión lambda que es la encargada de por cada elemento contable en data añadirlo dentro del cuerpo de la `LinkedList`.


## Pregunta 6

El destructor se define de la siguiente manera:

```cpp
Node::~Node()
{
	delete next;
	delete prev;
	delete data;
}

LinkedList::~LinkedList()
{
	delete head;
	delete tail;
}
```

### ¿Hace falta?

No son necesarios los destructores en este caso ya que cuando `C++` por defecto destruye un objeto, lo que hace es llamar al destructor de cada uno de los miembros del objeto. En este caso, como los miembros son punteros, se llama al destructor de cada uno de ellos, lo que hace que se libere la memoria que ocupan. Por lo tanto, no es necesario llamar al destructor de cada uno de los miembros del objeto.

### Punteros crudos

Un raw pointer es un puntero con un tiempo de vida no controlado en ningún objeto encapsulado.

#### ¿Por qué usar punteros crudos?

Si una función necesita un puntero y no tiene nada que ver con pertenencia, entonces es mejor usar un puntero crudo. Si sabes que una entidad debe tener un cierto tipo de pertenencia, entonces es mejor usar un puntero inteligente. Si no hay noción de pertenencia, entonces es mejor usar un puntero crudo.

Ejemplo1:

```cpp
void PrintObject(shared_ptr<const Object> po) // bad
{
    if(po)
      po->Print();
    else
      log_error();
}

void PrintObject(const Object* po) // good
{
    if(po)
      po->Print();
    else
      log_error();
}
```

```cpp
Object* createObject() // bad
{
    return new Object;
}

some_smart_ptr<Object> createObject() // good
{
   return some_smart_ptr<Object>(new Object);
}
```

## Pregunta 7

### Operador noexecpt

El operador `noexcept` comprueba en tiempo de compilación si una expresión no arroja una excepción. El operador noexcept no evalúa la expresión.

### Especificador noexcept

Al declarar una función, metodo o función lambda como `noexcept`, se especifica que estos no lanzan excepción y en el caso de hacerlo se para la ejecución del programa.
Dos buenas razones para el uso de `noexcept` son:
- Primero, un especificador de excepción documenta el comportamiento de la función. Si una función se especifica como `noexcept`, se puede usar de forma segura en una función que no arroja.
- En segundo lugar, es una oportunidad de optimización para el compilador. `noexcept` no puede llamar a `std::unexpected` y no puede deshacer la pila. La inicialización de un contenedor puede mover fácilmente los elementos al contenedor si el constructor de movimiento se declara como `noexcept`. Si no se declara como `noexcept`, los elementos pueden ser costosos de copiar en el contenedor.

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
template<class T>
using MyAllocList = std::list<T, MyAlloc<T>>;
```

### Puntero a funcion generica con alias

Con los visto en las secciones previas se puede crear un alias a un puntero de una función que permita cualquier cantidad de parámetros de cualquier tipo de la siguiente forma:

```cpp
template <class R, class... T>

using Func = R (*)(T...);
```

El código de arriba es el que tenemos implementado en el proyecto de la linked list.
