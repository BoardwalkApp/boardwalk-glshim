#!/bin/bash
set -e
rm -r gl || true
mkdir gl gl/wrap gl/math
LOCAL_PATH=`pwd`/../../src  
LIBRARIES="-L/home/zhuowei/Documents/winprogress/droid/twoprogramsoneproc/potatodroid/assets/ -lGLESv1_CM -ldl"
GL_SRC_FILES=`echo $LOCAL_PATH/gl/*.c $LOCAL_PATH/gl/wrap/*.c $LOCAL_PATH/gl/math/*.c`
CC="arm-linux-gnueabihf-gcc"
output_name="libglshim.so"
CFLAGS="-Wl,-soname,$output_name -Wl,--no-allow-shlib-undefined -rdynamic -std=c99 -O3 -I$LOCAL_PATH/../include -I$LOCAL_PATH/util -DBOARDWALK_POTATO"
outputs=""
for i in $GL_SRC_FILES
do
	objpath=`echo $i|sed -e s,$LOCAL_PATH/,, -e s/\\.c$/.o/`
	outputs="$outputs $objpath"
	$CC -c -o $objpath $CFLAGS -shared -fPIC $i $LIBRARIES
done
$CC -o $output_name $CFLAGS -shared -fPIC $outputs $LIBRARIES
