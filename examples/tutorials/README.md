# bxrabbitmq tutorials

https://www.rabbitmq.com/getstarted.html

## Required libraries

   BxRabbitMQ installed

## Build on Linux

```sh
$ mkdir -p /tmp/${USER}/bxrabbitmq/tutorials/_build.d
$ cd /tmp/${USER}/bxrabbitmq/tutorials/_build.d
$ cmake \
  -DCMAKE_INSTALL_PREFIX=../_install.d \
  $(bxrabbitmq-query --prefix)/share/BxRabbitMQ-$(bxrabbitmq-query --version)/examples/tutorials
$ make
$ make install
```

