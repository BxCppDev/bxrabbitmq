#!/usr/bin/env bash

# A Bash script to build and install devel BxRabbitMQ tutorials on Ubuntu (16.04).

opwd=$(pwd)
function my_exit()
{
    local error_code=$1
    shift 1
    cd ${opwd}
    exit ${error_code}
}

src_dir=$(pwd)
install_dir=$(pwd)/_install.d
build_dir=$(pwd)/_build.d

devel=false
bxrabbitmq_prefix=$(bxrabbitmq-query --prefix)

while [ -n "$1" ]; do
    opt="$1"
    if [ "${opt}" = "--bxrabbitmq-prefix" ]; then
	shift 1
	bxrabbitmq_prefix="$1"
    elif [ "${opt}" = "--devel" ]; then
	devel=true
    fi
    shift 1
done

if [ "x${bxrabbitmq_prefix}" = "x" ]; then
    if [ ${devel} = true ]; then
	bxrabbitmq_prefix="../../_install.d"
    else
	echo >&2 "[error] Missing BxRabbitMQ installation path! Abort!"
	my_exit 1
    fi
fi

if [ ! -d ${bxrabbitmq_prefix} ]; then
    echo >&2 "[error] No BxBxRabbitMQ installation! Abort!"
    my_exit 1
fi
cd ${bxrabbitmq_prefix}
bxrabbitmq_prefix=$(pwd)
echo >&2 "[info] BxRabbitMQ install dir = '${bxrabbitmq_prefix}'"
cd ${opwd}
export PATH="${bxrabbitmq_prefix}/bin:${PATH}"

which bxrabbitmq-query > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo >&2 "[error] BxRabbitMQ is not installed! Abort!"
    my_exit 1
else
    echo >&2 "[info] Found BxRabbitMQ config script."
fi

# brewsh
# curlpp_setup
# rabbitmqc_setup
# bxjsontools_setup

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
cmake \
    -DCMAKE_INSTALL_PREFIX="${install_dir}" \
    -DBxRabbitMQ_DIR="$(bxrabbitmq-query --cmakedir)" \
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
echo >&2 "[info] Installing..."
make install
if [ $? -ne 0 ]; then
    echo >&2 "[error] Installation failed! Abort!"
    my_exit 1
fi

my_exit 0

# end
