# bxrabbitmq
RabbitMQ client & server administration (C++ library)

The     ``bxrabbitmq``     library     (also   ``BxRabbitMQ``     or
``Bayeux/RabbitMQ``) consists in  a set of C++ API for RabbitMQ server
administration and Rabbit clients.

This is a very preliminary work that needs more development and tests.


## Dependencies and inspiration

bxrabbitmq makes use or is based on:
* rabbitmq-c for the client implemantation (https://github.com/alanxz/rabbitmq-c)
* pika for the client API (https://github.com/pika/pika)
* RabbitMQ HTTP-based API for server admin (https://www.rabbitmq.com/management.html)

## License:

See the ``LICENSE.txt`` file and the ``licensing`` directory.


### Build and install:


  PRE:

     add PKG_CONFIG_PATH to RabbitC defs
     => export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/path/to/rabbitc/install/dir/lib/../pkgconfig

     add PATH to bxjsontools-query

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

### Enjoy bxrabbitmq from its installation directory:
```sh
$ LANG="C" tree ${HOME}/sw/bxrabbitmq/_install.d
├── bin
│   └── bxrabbitmq-query
├── include
│   └── bayeux
│       └── rabbitmq
│           ├── basic_properties.h
│           ├── channel.h
│           ├── config.h
│           ├── connection.h
│           ├── parameters.h
│           └── version.h
├── lib
│   ├── cmake
│   │   └── BxRabbitMQ-0.1.0
│   │       ├── BxRabbitMQConfig.cmake
│   │       ├── BxRabbitMQConfigVersion.cmake
│   │       ├── BxRabbitMQTargets.cmake
│   │       └── BxRabbitMQTargets-noconfig.cmake
│   └── libBayeux_rabbitmq.so
└── share
└── BxRabbitMQ-0.1.0
├── examples
│   ├── add_links.sh
│   ├── management
│   │   ├── ex1.cxx
│   │   └── ex2.cxx
│   └── tutorials
│       ├── CMakeLists.txt
│       ├── README.md
│       ├── t1_receive.cxx
│       ├── t1_send.cxx
│       ├── t2_new_task.cxx
│       ├── t2_worker.cxx
│       ├── t3_emit_log.cxx
│       ├── t3_receive_logs.cxx
│       ├── t4_emit_log_direct.cxx
│       ├── t4_receive_logs_direct.cxx
│       ├── t5_emit_logs_topic.cxx
│       ├── t5_emit_log_topic.cxx
│       ├── t5_receive_logs_topic.cxx
│       ├── t6_rpc_client.cxx
│       └── t6_rpc_server.cxx
├── LICENSE.txt
└── licensing
└── bxrabbitmq
└── LICENSE.txt


## Using bxrabbitmq:

* The ``bxrabbitmq-query`` utility allows you to fetch informations about your
  BxRabbitMQ installation. You may add the following typical line in your
``~/.bashrc`` profile:
```sh
export PATH="${HOME}/sw/bxrabbitmq/_install.d/bin:${PATH}"
```
  This will give you access to the ``bxrabbitmq-query`` command-line utility:
```sh
$ bxrabbitmq-query --help
```

* There is simple examples based on RabbitMQ tutorials (https://www.rabbitmq.com/getstarted.html)
that illustrates simple usecases.

```sh
cat $(bxrabbitmq-query --prefix)/share/BxRabbitMQ-$(bxrabbitmq-query --version)/examples/tutorials/README.md
```


