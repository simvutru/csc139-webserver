cd ..

# compile your code
make

# run server
./build/wserver -d www -p 8000 -t 128 -b 1024 >> log.txt &

# run client to generate request
req1="http://localhost:8000/home.html"
# 1. Basic request (100 total requests, 10 at a time)
ab -n 100000 -c 100 $req1 

req2="http://localhost:8000/cgi-bin/adder?4&5"

# 3. CGI script (Adder) - note the quotes to handle '&'
ab -n 5000 -c 50 $req2 

(echo $req1; echo $req2) | parallel 'ab -n 100 -c 10 {}'

# 4. CGI script (Spin) - testing long-running threads
req3="http://localhost:8000/cgi-bin/spin?2"
ab -n 20 -c 4 $req3

# kill server
pgrep -l wserver
pkill wserver
