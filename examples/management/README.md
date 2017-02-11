# Rabbit server management

  https://www.rabbitmq.com/getstarted.html


## Required libraries

   BxRabbitMQ installed with cmake option ``-DBXRABBITMQ_WITH_MANAGER=ON``

## Build on Linux:

```sh
$ mkdir -p /tmp/${USER}/bxrabbitmq/management/_build.d
$ cd /tmp/${USER}/bxrabbitmq/management/_build.d
$ cmake \
  -DCMAKE_INSTALL_PREFIX=../_install.d \
  -DBxRabbitMQ_DIR="${bxrabbitmq-query --cmakedir}"    \
  $(bxrabbitmq-query --prefix)/share/BxRabbitMQ-$(bxrabbitmq-query --version)/examples/management
$ make
$ make install
```

