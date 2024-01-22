build:
	CGO_ENABLED=1 GOOS=linux GOARCH=amd64 CC=x86_64-linux-gnu-gcc \
 	go build -ldflags " \
 	-s -extldflags=-Wl,-z,lazy \
	" -o main -v .

build2:
	CGO_ENABLED=0 GOOS=linux GOARCH=amd64 CC=x86_64-linux-gnu-gcc \
 	go build -ldflags " \
 	-s -extldflags=-Wl,-z,lazy \
	" -o main -v .