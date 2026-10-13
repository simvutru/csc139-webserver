cd ..

# compile your code
make

# run server
./build/wserver -d www -p 8000 -t 4 -b 16 >> log.txt &

# run client to generate request

curl localhost:8000/

curl localhost:8000/home.html
curl localhost:8000/cgi-bin/adder?4\&5
curl localhost:8000/cgi-bin/spin?2


# kill server
echo ""
echo "Complete the testing and Stop the server"
pgrep -l wserver
pkill wserver
