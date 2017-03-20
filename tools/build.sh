#!/usr/bin/env bash

# A Bash script to build and install devel BxRabbitMQ on Ubuntu (16.04).

opwd=$(pwd)
function my_exit()
{
    local error_code=$1
    shift 1
    cd ${opwd}
    exit ${error_code}
}

function do_usage()
{

    cat<<EOF

build.sh [options]

Options:

  --help   print this help then exit
  --mgr    build the RabbitMQ management API
  --bxjsontools-prefix path
           set the bxjsontools installation prefix (implies --mgr)

EOF
    return 0
}

src_dir=$(pwd)
install_dir=$(pwd)/_install.d
build_dir=$(pwd)/_build.d

devel=false
bxjsontools_prefix=$(bxjsontools-query --prefix)
with_management=false

while [ -n "$1" ]; do
    opt="$1"
    if [ "${opt}" = "--help" ]; then
	do_usage
    	my_exit 0
    elif [ "${opt}" = "--mgr" ]; then
    	with_management=true
    elif [ ${with_management} = true -a "${opt}" = "--bxjsontools-prefix" ]; then
	shift 1
	bxjsontools_prefix="$1"
    fi
    shift 1
done

# brewsh
# curlpp_setup
# rabbitmqc_setup
# bxjsontools_setup

if [ ${with_management} = true ]; then
    echo >&2 "[info] Checking cURLpp..."
    pkg-config --list-all | grep curlpp >/dev/null 2>&1
    if [ $? -ne 0 ]; then
	echo >&2 "[error] Missing cURLpp setup! Abort!"
	my_exit 1
    fi
    echo >&2 "[info] Checking BxJsontools..."
    which bxjsontools-query >/dev/null 2>&1
    if [ $? -ne 0 ]; then
	echo >&2 "[error] Missing BxJsontools setup! Abort!"
	my_exit 1
    fi

    if [ "x${bxjsontools_prefix}" = "x" ]; then
	bxjsontools_prefix="$(bxjsontools-query --cmakedir)"
    fi
fi

echo >&2 "[info] Checking RabbitMQ-C..."
pkg-config --list-all | grep rabbitmq-c >/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo >&2 "[error] Missing RabbitMQ-C setup! Abort!"
    my_exit 1
fi

if [ -d ${install_dir} ]; then
    rm -fr ${install_dir}
fi

if [ -d ${build_dir} ]; then
    rm -fr ${build_dir}
fi

mkdir -p ${build_dir}

cd ${build_dir}
echo >&2 ""
echo >&2 "[info] Configuring..."
with_mgr_opts=""
if [ ${with_management} = true ]; then
    with_mgr_opts="-DBxJsontools_DIR=${bxjsontools_prefix}"
fi
cmake \
    -DCMAKE_INSTALL_PREFIX="${install_dir}" \
    -DBXRABBITMQ_WITH_MANAGER=${with_management} \
    ${with_mgr_opts} \
    ${src_dir}
if [ $? -ne 0 ]; then
    echo >&2 "[error] CMake failed! Abort!"
    my_exit 1
fi

echo >&2 ""
echo >&2 "[info] Building..."
make -j4
if [ $? -ne 0 ]; then
    echo >&2 "[error] Build failed! Abort!"
    my_exit 1
fi

echo >&2 ""
echo >&2 "[info] Testing..."
make test
if [ $? -ne 0 ]; then
    echo >&2 "[error] Testing failed! Abort!"
    my_exit 1
fi

echo >&2 ""
echo >&2 "[info] Installing..."
make install
if [ $? -ne 0 ]; then
    echo >&2 "[error] Installation failed! Abort!"
    my_exit 1
fi

my_exit 0

# end
