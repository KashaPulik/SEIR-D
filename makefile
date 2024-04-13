all: app chart.png
	code chart.png

app: main.c
	gcc -Wall -o app main.c

chart.png: draw.py data.txt app
	./app
	python3 draw.py

data.txt: main.c

clean:
	rm -rf app chart.png data.txt