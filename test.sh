if [ -z "$1" ]
then
      ./bin/tests
else
      ./bin/tests --gtest_filter=$1
fi
