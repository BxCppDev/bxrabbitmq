# bxrabbitmq tutorials
https://www.rabbitmq.com/getstarted.html

## Build example on Linux

#
#  Required libraries : RabbitC & BxRabbitMQ
#
#  add PATH to BxRabbitMQ install bin dir (to find bxrabbitmq-query)
#  => export PATH=$PATH:/path/to/bxrabbitmq/install/dir/bin
#
#  add PKG_CONFIG_PATH to RabbitC defs
#  => export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/path/to/rabbitc/install/dir/lib/../pkgconfig
#

```sh
$ mkdir -p /tmp/${USER}/bxrabbitmq/tutorials/_build.d
$ cd /tmp/${USER}/bxrabbitmq/tutorials/_build.d
$ cmake \
  -DCMAKE_INSTALL_PREFIX=../_install.d \
  $(bxrabbitmq-query --prefix)/share/BxRabbitMQ-$(bxrabbitmq-query --version)/examples/tutorials
$ make
$ make install
```

