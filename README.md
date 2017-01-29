# bxrabbitmq
RabbitMQ client & server administration (C++ library)

The     ``bxrabbitmq``     library     (also   ``BxRabbitMQ``     or
``Bayeux/RabbitMQ``) consists in  a set of C++ API for RabbitMQ server
administration and Rabbit clients.

This is a very preliminary work that needs more development and tests.


## Dependencies and inspiration

bxrabbitmq makes use or is based on:
* rabbitmq-c for the client implementation (https://github.com/alanxz/rabbitmq-c)
* pika for the client API (https://github.com/pika/pika)
* RabbitMQ HTTP-based API for server admin (https://www.rabbitmq.com/management.html)

bxrabbitmq depends on:
* The RabbitMQ-C client library (https://github.com/alanxz/rabbitmq-c),
* Boost (version >=1.58, but former version may work)
* cURLpp (https://github.com/jpbarrette/curlpp) for server management,
* BxJsontools (https://github.com/BxCppDev/bxjsontools) for server management,
* CMake and pkgconfig for build and install.

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

**Note for SuperNEMO users:**
Cadfaelbrew (https://github.com/SuperNEMO-DBD/brew) is used to build, install and manage
the SuperNEMO experiment software. It provides formula for CMake, Doxygen, Boost, curl, libssl...
and various other software that should be used in place of system packages.

2017-01-29: brew formula for curlpp, rabbitmq-c, bxjsontools and bxrabbitmq are not available yet.

### Download the source code from GitHub:
```sh
$ mkdir -p ${HOME}/bxrabbitmq/_source.d/
$ cd       ${HOME}/bxrabbitmq/_source.d/
$ git clone https://github.com/BxCppDev/bxrabbitmq.git
```

```sh
$ mkdir -p ${HOME}/bxrabbitmq/_build.d/
$ cd       ${HOME}/bxrabbitmq/_build.d/
$ cmake -DCMAKE_INSTALL_PREFIX=../_install.d  ../_source.d/bxrabbitmq
$ make
$ make test
$ make install
```

## Using bxrabbitmq:

* The ``bxrabbitmq-query`` utility allows you to fetch informations about your
  BxRabbitMQ installation. You may add the following typical line in your
``~/.bashrc`` profile:
```sh
export PATH="${HOME}/bxrabbitmq/_install.d/bin:${PATH}"
```
  This will give you access to the ``bxrabbitmq-query`` command-line utility:
```sh
$ bxrabbitmq-query --help
```

* There are simple examples based on RabbitMQ tutorials (https://www.rabbitmq.com/getstarted.html)
that illustrate simple usecases.

```sh
cat $(bxrabbitmq-query --prefix)/share/BxRabbitMQ-$(bxrabbitmq-query --version)/examples/tutorials/README.md
```