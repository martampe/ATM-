Estructura de la Base de Datos Bancaria
La base de datos que hemos creado representa un sistema bancario completo con usuarios, cuentas, tarjetas y transacciones. Vamos a analizar cómo está estructurada y cómo se relacionan todos los elementos entre sí.
Tablas Principales
1. Tabla de Usuarios
Esta tabla almacena la información personal de los clientes del banco. Cada usuario se identifica de manera única por su DNI. Contiene datos como:

DNI (identificador único)
Nombre y apellido
Fecha de nacimiento
Información de contacto (email, teléfono)
Credenciales de seguridad (contraseña, pregunta de seguridad)
Dirección

Este es el punto de partida de nuestro sistema, ya que un cliente puede tener múltiples cuentas y accesos.
2. Tabla de Cuentas
Representa las cuentas bancarias en el sistema. Cada cuenta tiene:

Número de cuenta (IBAN, identificador único)
Saldo actual
Tipo de cuenta (referencia a TipoCuent)
Fecha de creación
Estado (referencia a EstadoCuent)
DNI del titular (referencia a Usuario)

Una cuenta pertenece a un titular principal (dniTitular), pero puede ser accesible por varios usuarios a través de la tabla de Acceso.
3. Tabla de Tarjetas
Contiene información sobre las tarjetas vinculadas a las cuentas:

Número de tarjeta (identificador único)
Fecha de caducidad
CVV y PIN
Estado (referencia a EstadoTar)
Número de cuenta asociada (referencia a Cuenta)

Cada tarjeta está asociada a una única cuenta, pero una cuenta puede tener múltiples tarjetas.
4. Tabla de Transacciones
Registra los movimientos financieros en el sistema:

ID de transacción (identificador único)
Número de cuenta origen (para transferencias)
Número de tarjeta origen (para pagos con tarjeta)
Número de cuenta destino (para transferencias e ingresos)
Cantidad
Fecha
Dirección del ATM (para operaciones en cajeros)
Estado (referencia a EstadoTrans)
Tipo (referencia a TipoTrans)

Esta tabla maneja cuatro tipos distintos de transacciones:

Transferencias (tipo 1): Tienen cuenta origen y destino, sin tarjeta ni ATM.
Pagos con tarjeta (tipo 2): Solo incluyen número de tarjeta, sin cuenta destino.
Retiros en efectivo (tipo 3): Incluyen dirección del ATM, sin cuenta destino ni tarjeta.
Ingresos en efectivo (tipo 4): Incluyen cuenta destino y dirección del ATM.

5. Tabla de Acceso Usuarios-Cuentas
Establece las relaciones entre usuarios y cuentas:

DNI del usuario (referencia a Usuario)
Número de cuenta (referencia a Cuenta)

Esta tabla implementa una relación muchos a muchos: un usuario puede acceder a múltiples cuentas, y una cuenta puede ser accesible por múltiples usuarios.
Tablas de Catálogo
Estas tablas contienen valores predefinidos que se usan como referencia en las tablas principales:
1. EstadoTar
Define los posibles estados de una tarjeta (Activa, Bloqueada, Caducada, etc.).
2. TipoTar
Define los tipos de tarjetas disponibles (Débito, Crédito, Prepago, etc.).
3. EstadoCuent
Define los posibles estados de una cuenta (Activa, Inactiva, Bloqueada, etc.).
4. TipoCuent
Define los tipos de cuentas disponibles (Corriente, Ahorro, Nómina, etc.).
5. EstadoTrans
Define los posibles estados de una transacción (Completada, Pendiente, Rechazada, etc.).
6. TipoTrans
Define los tipos de transacciones permitidas (Transferencia, Pago con tarjeta, Retiro, Ingreso).
