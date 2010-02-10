
if [ $# -ne 3 ]
then
   echo "usage: $0 <module name> <data mode> <os>"
   exit -1
fi

module_name=$1
data_mode=$2
c_program_name=_get_version.c
export_name=_get_version.exp
version=`date +%y%m%d.%H%M%S`
if [ "$3" = "_AIX_SYSTEM_" ]
then
	data_mode="-q${data_mode}"
else
	data_mode="+DD${data_mode}"
fi

echo "\
#include <stdio.h>
#include <stdlib.h>

int _get_version(char *name, char *version)
{
    strcpy(name,\"${module_name}\");
    strcpy(version,\"${version}\");
    return (0);
}

" > ${c_program_name}

cc ${data_mode} -c ${c_program_name}
echo "_get_version" > $export_name
rm ${c_program_name}
