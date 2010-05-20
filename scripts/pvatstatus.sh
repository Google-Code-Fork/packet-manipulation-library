#!/bin/bash
SCRIPT_DIRECTORY=/home/scap/scripts
CHECKOUT_DIRECTORY=/tmp/pvat
WEB_DIRECTORY=/var/www/pvatStatus

rm -rf ${CHECKOUT_DIRECTORY}
rm ${SCRIPT_DIRECTORY}/configure.txt
rm ${SCRIPT_DIRECTORY}/make.txt
rm ${SCRIPT_DIRECTORY}/makeTest.txt
rm ${SCRIPT_DIRECTORY}/test.txt

svn co http://code.scaparra.com/PacMan ${CHECKOUT_DIRECTORY}
cd ${CHECKOUT_DIRECTORY}
./configure.sh &> ${SCRIPT_DIRECTORY}/configure.txt
make &> ${SCRIPT_DIRECTORY}/make.txt
if [ $? -ne 0 ];
then
	cp ${SCRIPT_DIRECTORY}/compileFail.html ${WEB_DIRECTORY}/index.html
fi

cd ${CHECKOUT_DIRECTORY}/Test && make &> ${SCRIPT_DIRECTORY}/makeTest.txt
if [ $? -ne 0 ];
then 
	cp ${SCRIPT_DIRECTORY}/compileTestFail.html ${WEB_DIRECTORY}/index.html
fi

cd ${CHECKOUT_DIRECTORY}/Test && ./test &> ${SCRIPT_DIRECTORY}/test.txt
if [ $? -ne 0 ];
then
  cp ${SCRIPT_DIRECTORY}/testFail.html ${WEB_DIRECTORY}/index.html
else
	cp ${SCRIPT_DIRECTORY}/win.html ${WEB_DIRECTORY}/index.html
fi

cp ${SCRIPT_DIRECTORY}/configure.txt ${WEB_DIRECTORY}
cp ${SCRIPT_DIRECTORY}/make.txt ${WEB_DIRECTORY}
cp ${SCRIPT_DIRECTORY}/makeTest.txt ${WEB_DIRECTORY}
cp ${SCRIPT_DIRECTORY}/test.txt ${WEB_DIRECTORY}


cd ${SCRIPT_DIRECTORY}

