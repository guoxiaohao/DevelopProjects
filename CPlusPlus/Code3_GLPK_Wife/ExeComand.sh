BuildDir="build"
if ! [ -d $BuildDir ];then
   mkdir $BuildDir
fi
cd $BuildDir
echo "Compile"
cmake ..
make -j2
cp ../supers_days_16.csv ./
