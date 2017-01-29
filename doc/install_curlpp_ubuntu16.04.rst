============================================================================
 Installation of the curlpp 0.7.4 on Ubuntu 16.04
============================================================================


:Author: F.Mauger
:Contact: mauger@lpccaen.in2p3.fr
:Date:   2017-01-28
:Version: 0.1

In this document  we propose an installation procedure  for the cURLpp
0.7.4,  on top  of  Xubuntu  16.04 LTS  (Xenial  Xerus)  for a  system
(64-bits).

.. contents::


Links
------------

* https://github.com/jpbarrette/curlpp

Install RabbitMQ C client
------------------------------

* Dependencies:

  * ``pkgconfig`` (0.29.1) from Cadfaelbrew
  * ``curl`` (7.50.1) from Cadfaelbrew

* From Cadfaelbrew, we get:

.. code:: sh

   $ brewsh
   $ brew info pkgconfig
   ...
   $ brew info curl
   ...
..

* Download:

.. code:: sh

   $ mkdir -p /opt/sw/cURLpp
   $ cd /opt/sw/cURLpp
   $ git clone https://github.com/jpbarrette/curlpp
   $ tar xvzf curlpp/curlpp-0.7.4-beta.tar.gz
   $ cd curlpp-0.7.4-beta/
..

* Build/installation:

.. code:: sh

   $ CPPFLAGS=-I/opt/sw/SuperNEMO-DBD/Cadfaelbrew/include \
     CXXFLAGS=--std=c++11 \
     LDFLAGS=-L/opt/sw/SuperNEMO-DBD/Cadfaelbrew/lib \
          ./configure --prefix=/opt/sw/cURLpp/install-0.7.4
   $ make -j4
   $ make install
..

* Setup (in ``~/.bashrc`` or any suitable startup script):

.. code:: sh

   function do_curlpp_074_setup()
   {
     if [ -n "${CURLPP_INSTALL_DIR_INSTALL_DIR}" ]; then
	echo "WARNING: cURLpp library is already setup !" >&2
	return 1
     fi
     export CURLPP_INSTALL_DIR="/opt/sw/cURLpp/install-0.7.4"
     export PATH="${CURLPP_INSTALL_DIR}/bin:${PATH}"
     export PKG_CONFIG_PATH="${CURLPP_INSTALL_DIR}/lib/pkgconfig:${PKG_CONFIG_PATH}"
     echo "NOTICE: cURLpp library is now setup !" >&2
     return 0
   }
   export -f do_curlpp_074_setup

   # Special aliases:
   alias curlpp_setup="do_curlpp_074_setup"
..
