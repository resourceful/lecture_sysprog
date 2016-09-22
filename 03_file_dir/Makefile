texfile = 03-filedirs.tex

all: ${texfile}
	pdflatex --shell-escape $< 

clean:
	rm *.aux *.log *.nav *.out *.snm *.toc *.vrb

o: ${texfile}
	gv $(basename $<).pdf  &

