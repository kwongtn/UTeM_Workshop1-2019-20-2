docker build --tag attmgmt-db:1.0 .

docker run -p 3306:3306 -p 33060:33060 attmgmt-db