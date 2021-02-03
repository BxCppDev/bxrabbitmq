# bxrabbitmq
RabbitMQ client & server administration (C++ library)

The     ``bxrabbitmq``     library     (also   ``BxRabbitMQ``     or
``Bayeux/RabbitMQ``) consists in  a C++ API for RabbitMQ server
administration and Rabbit clients.

This is a very preliminary work that needs more development and tests.

bxrabbitmq  has  been initiated  in  the  framework of  the  SuperNEMO
physics experiment software.

## Versions

Current version: 1.0.0 (2021-02-03)


## Dependencies and inspiration

bxrabbitmq makes use or is based on:
* rabbitmq-c for the client implementation (https://github.com/alanxz/rabbitmq-c)
* pika for the client API (https://github.com/pika/pika)
* RabbitMQ HTTP-based API for server admin (https://www.rabbitmq.com/management.html)

bxrabbitmq depends on:

* The RabbitMQ-C client library (https://github.com/alanxz/rabbitmq-c)

  * On Ubuntu 18.04 : librabbitmq 0.8.0
  * On Ubuntu 20.04 : librabbitmq 0.10.0
  
  ```
  $ sudo apt-get install librabbitmq-dev
  ```

* Boost (version >=1.65, but former version may work)

  * On Ubuntu 18.04 : Boost 1.65.1
  * On Ubuntu 20.04 : Boost 1.71.0
  
  ```
  $ sudo apt-get install libboost-all-dev
  ```

* cURLpp (https://github.com/jpbarrette/curlpp) for optional server management code

  * On Ubuntu 18.04 : libcurl 7.58.0
  * On Ubuntu 20.04 : libcurl 7.68.0
  
  ```
  $ sudo apt-get install libcurl4-openssl-dev libcurl4
  $ sudo apt-get install libcurlpp-dev
  ```

* BxJsontools (https://github.com/BxCppDev/bxjsontools) for optional server management code
  
* CMake and pkgconfig for build and install

  * On Ubuntu 18.04 : CMake 3.10.2, pkg-config 0.29.1
  * On Ubuntu 20.04 : CMake 3.16.3, pkg-config 0.29.1
  
  ```
  $ sudo apt-get install cmake pkg-config
  ```

## License:

See the ``LICENSE.txt`` file and the ``licensing`` directory.


### Build and install:

CMake options:
* ``BXRABBITMQ_WITH_MANAGER`` for building RabbitMQ management code (default=``OFF``). This implies
  cURLpp and BxJsontools (see above).

Prerequisites:

* update ``PKG_CONFIG_PATH`` to RabbitMQ-C client library pkgconfig description ``librabbitmq.pc``:
```sh
$ export PKG_CONFIG_PATH=/path/to/rabbitc/install/dir/lib/../pkgconfig:${PKG_CONFIG_PATH}
```
* update ``PATH`` to ``bxjsontools-query`` (only for client management code):
```sh
$ export PATH=/path/to/bxjsontools/install/dir/bin:${PATH}
```
* update ``PKG_CONFIG_PATH`` to cURLpp library pkgconfig description ``curlpp.pc`` (only for client management code):
```sh
$ export PKG_CONFIG_PATH=/path/to/curlpp/install/dir/lib/../pkgconfig:${PKG_CONFIG_PATH}
```
* make sure Boost is installed on your system and CMake has a proper ``FindBoost`` module:
```sh
$ cmake --help-module FindBoost
```

**Note:**

* 2017-09-26: (OBSOLETE 2020-02-03) :
Linuxbrew formula for rabbitmq-c is available from Linuxbrew
core tap. Formulas for bxjsontools and bxrabbitmq are available from
the  https://github.com/BxCppDev/homebrew-bxtap.

### Download the source code from GitHub:

* Download the source code from the default ``develop`` branch:

```sh
$ mkdir -p ${HOME}/bxrabbitmq/_source.d/
$ cd       ${HOME}/bxrabbitmq/_source.d/
$ git clone https://github.com/BxCppDev/bxrabbitmq.git bxrabbitmq
```

or, for a specific tag:

```sh
$ git clone -b '0.4.2' --single-branch https://github.com/BxCppDev/bxrabbitmq.git bxrabbitmq-0.4.2
```

* Configure, build, install:

```sh
$ mkdir -p ${HOME}/bxrabbitmq/_build.d/
$ cd       ${HOME}/bxrabbitmq/_build.d/
$ cmake -DCMAKE_INSTALL_PREFIX=../_install.d ../_source.d/bxrabbitmq[-0.4.2]
$ make
$ make test
$ make install
```

Supported options and configuration parameters:

* ``BXRABBITMQ_WITH_MANAGER`` : flag to build the RabbitMQ server management API (implies ``curlpp``
   and ``bxjsontools``, default: ``OFF``),
* ``BOOST_ROOT`` : path to your installation of Boost libraries.

Example:
```sh
$ mkdir -p ${HOME}/bxrabbitmq/_build.d/
$ cd       ${HOME}/bxrabbitmq/_build.d/
$ cmake \
    -DCMAKE_INSTALL_PREFIX=../_install.d \
    -DBXRABBITMQ_WITH_MANAGER=ON \
    -DBxJsontools_DIR=$(bxjsontools-query --cmakedir) \
    ../_source.d/bxrabbitmq[-0.4.2]
$ make
$ make test
$ make install
```

### Quickstart build tools:

```sh
$ ./tools/build.sh --mgr --boost-prefix $(brew --prefix boost)
```


## Using bxrabbitmq:

* The ``bxrabbitmq-query`` utility allows you to fetch informations about your
  BxRabbitMQ installation. You may add the following typical line in your
``~/.bashrc`` profile:
```sh
export PATH="${HOME}/bxrabbitmq/_install.d/bin:${PATH}"
```
  This  will give  you access  to the  ``bxrabbitmq-query`` command-line utility:
```sh
$ bxrabbitmq-query --help
```

* There   are   simple   examples    based   on   RabbitMQ   tutorials
(https://www.rabbitmq.com/getstarted.html)   that  illustrate   simple
usecases.
```sh
$ cat $(bxrabbitmq-query --prefix)/share/BxRabbitMQ-$(bxrabbitmq-query --version)/examples/tutorials/README.md
```

* CMake  configuration  scripts (i.e.  ``BxRabbitMQConfig.cmake``  and
  ``BxRabbitMQConfigVersion.cmake``)    are    provided    for    client
  software. The  CMake ``find_package(BxRabbitmq REQUIRED CONFIG)`` command
  can  be   given  the  following   variable  to  find   the  BxRabbitMQ
  installation on your system:
```sh
$ cmake ... -DBxRabbitMQ_DIR="$(bxrabbitmq-query --cmakedir)" ...
```
