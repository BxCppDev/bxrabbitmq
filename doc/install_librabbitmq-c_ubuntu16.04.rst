============================================================================
 Installation of the librabbitmq C client 0.8.0  on Ubuntu 16.04
============================================================================


:Author: F.Mauger
:Contact: mauger@lpccaen.in2p3.fr
:Date:   2017-01-23
:Version: 0.1

In  this  document  we  propose  an  installation  procedure  for  the
RabbitMQ-C Client  0.8.0, on top  of Xubuntu 16.04 LTS  (Xenial Xerus)
for a system (64-bits).

.. contents::


Links
------------

* https://www.rabbitmq.com/install-debian.html
* https://github.com/alanxz/rabbitmq-c


Install RabbitMQ C client
------------------------------

* Dependencies:

.. code:: sh

   $ sudo apt-get install libpopt-dev
   $ sudo apt-get install xmlto xmltoman
..


* From Cadfaelbrew, we get:

.. code:: sh

   $ brewsh
   $ which openssl
   /opt/sw/SuperNEMO-DBD/Cadfaelbrew/bin/openssl
   $ which doxygen
   /opt/sw/SuperNEMO-DBD/Cadfaelbrew/bin/doxygen
..

* Download:

.. code:: sh

   $ cd /opt/sw
   $ mkdir librabbitmq-c
   $ cd librabbitmq-c
   $ wget https://github.com/alanxz/rabbitmq-c/archive/v0.8.0.tar.gz
   $ tar xvzf v0.8.0.tar.gz
..

* Build/installation:

.. code:: sh

   $ mkdir _build.d
   $ cd _build.d
   $ cmake \
      -DCMAKE_INSTALL_PREFIX=/opt/sw/librabbitmq-c/install-0.8.0 \
      -DBUILD_EXAMPLES=ON \
      -DBUILD_SHARED_LIBS=ON \
      -DBUILD_TESTS=ON \
      -DBUILD_TOOLS=ON \
      -DBUILD_TOOLS_DOCS=ON \
      -DENABLE_SSL_SUPPORT=ON \
      -DENABLE_THREAD_SAFETY=ON \
      -DBUILD_API_DOCS=ON \
      ../rabbitmq-c-0.8.0
   $ make -j4
   $ make install
..

* Setup (in ``~/.bashrc`` or any suitable startup script):

.. code:: sh

   function do_rabbitmqc_080_setup()
   {
     if [ -n "${RABBITMQC_INSTALL_DIR}" ]; then
	echo "WARNING: RabbitMQ-C client library is already setup !" >&2
	return 1
     fi
     export RABBITMQC_INSTALL_DIR="/opt/sw/librabbitmq-c/install-0.8.0"
     export PKG_CONFIG_PATH="${RABBITMQC_INSTALL_DIR}/lib/x86_64-linux-gnu/pkgconfig:${PKG_CONFIG_PATH}"
     export PATH="${RABBITMQC_INSTALL_DIR}/bin:${PATH}"
     export MANPATH="${RABBITMQC_INSTALL_DIR}/share/man:${MANPATH}"
     echo "NOTICE: RabbitMQ-C client library is now setup !" >&2
     return 0
   }
   export -f do_rabbitmqc_080_setup

   # Special aliases:
   alias rabbitmqc_setup="do_rabbitmqc_080_setup"
..
