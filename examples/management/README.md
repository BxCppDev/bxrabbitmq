# bxrabbitmq rabbit_management
# https://www.rabbitmq.com/getstarted.html webapi

## Build example on Linux

#
#  Required libraries : RabbitC & BxRabbitMQ & BxJsontools
#
#  add PATH to BxRabbitMQ install bin dir (to find bxrabbitmq-query)
#  => export PATH=$PATH:/path/to/bxrabbitmq/install/dir/bin
#
#  add PKG_CONFIG_PATH to RabbitC defs
#  => export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/path/to/rabbitc/install/dir/lib/../pkgconfig
#

```sh
$ mkdir -p /tmp/${USER}/bxrabbitmq/management/_build.d
$ cd /tmp/${USER}/bxrabbitmq/management/_build.d
$ cmake \
  -DCMAKE_INSTALL_PREFIX=../_install.d \
  -DCMAKE_FIND_ROOT_PATH="${bxjsontools-query --prefix}" \
  -DBxJsontools_DIR="${bxjsontools-query --cmakedir}"    \
  $(bxrabbitmq-query --prefix)/share/BxRabbitMQ-$(bxrabbitmq-query --version)/examples/management
$ make
$ make install
```

